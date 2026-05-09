// save_load.c
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include "save_load.h"

static const unsigned char IV[16] = "BlackJackMatisse";


// Avec une grande aide de l'IA sur le coup, trop avancé pour moi.
static void get_machine_key(unsigned char key[32]) {
    char buf[256] = {0};

    #ifdef _WIN32
        DWORD serial = 0;
        GetVolumeInformationA("C:\\", NULL, 0, &serial, NULL, NULL, NULL, 0);
        snprintf(buf, sizeof(buf), "win-%lu-secret-matis", serial);
    #else
        FILE *f = fopen("/etc/machine-id", "r");
        if (f) { fgets(buf, sizeof(buf), f); fclose(f); }
        else snprintf(buf, sizeof(buf), "fallback-secret-matis");
    #endif

    SHA256((unsigned char *)buf, strlen(buf), key);
}

int save_encrypted(const char *path, void *data, size_t len) {
    unsigned char key[32];
    get_machine_key(key);

    unsigned char buf[4096];
    int out_len, final_len;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, IV);
    EVP_EncryptUpdate(ctx, buf, &out_len, data, len);
    EVP_EncryptFinal_ex(ctx, buf + out_len, &final_len);
    EVP_CIPHER_CTX_free(ctx);

    FILE *f = fopen(path, "wb");
    if (!f) return 0;
    fwrite(buf, 1, out_len + final_len, f);
    fclose(f);
    return 1;
}

int load_encrypted(const char *path, void *data) {
    unsigned char key[32];
    get_machine_key(key);

    unsigned char buf[4096];
    int out_len, final_len;

    FILE *f = fopen(path, "rb");
    if (!f) return 0;
    size_t bytes_read = fread(buf, 1, sizeof(buf), f);
    fclose(f);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, IV);
    EVP_DecryptUpdate(ctx, data, &out_len, buf, bytes_read);
    int ok = EVP_DecryptFinal_ex(ctx, (unsigned char *)data + out_len, &final_len);
    EVP_CIPHER_CTX_free(ctx);

    return ok == 1;
}