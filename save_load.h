#ifndef SAVEL_H
#define SAVEL_H

#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

int save_encrypted(const char *path, void *data, size_t len);
int load_encrypted(const char *path, void *data);

#endif