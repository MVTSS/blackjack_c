#define _POSIX_C_SOURCE 200809L // Pour enlever les erreurs avec sigaction incomplet
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "save_load.h"
#include "language.h"
#include "config.h"


void redirect(int signum) { // si Ctrl + C pour sortir
    if (signum == SIGINT) {
        Language_Pack* lang = get_language_pack();
        printf("%s", lang->init_money_early_leave);
        exit(0);
    }
}



int main() {
    init_languages();
    load_config();
    set_language(get_language_from_config());

    Language_Pack* lang = get_language_pack();
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler = redirect;
    sigaction(SIGINT,&act,NULL);


    char* fname = "./blackjack_bank";
    int init_money = 100, loaded_money;
    int contain_data;
    if (access(fname, F_OK) == 0) {
        // check si le fichier est vide
        struct stat stat_record;
        if (stat(fname, &stat_record)) { perror("Error stat"); return -1; }
        if (stat_record.st_size <= 1)
        {
            printf("%s", lang->init_money_bank_already_exist);
        } else
        {
            printf("%s", lang->init_money_file_already_exist);
            contain_data = 1;
        }
        

    } else {
        printf("%s", lang->init_money_bank_doesnt_exist);
    }


    char ans;


    if (contain_data)
    {
        load_encrypted(fname, &loaded_money);
        printf(lang->init_money_bank_loaded, loaded_money);
    }
    

    scanf("%c", &ans);
    puts("");
    switch (ans)
    {
    case 'Y':
    case 'y':
        printf("%s", lang->init_money_bankrupt);
        save_encrypted(fname, &init_money, sizeof(init_money));
        load_encrypted(fname, &loaded_money);
        printf(lang->init_money_added_to_bank, loaded_money);
        break;
    
    default:
        printf("%s\n", lang->init_money_your_call);
        puts("-- Money NOT added");
        break;
    }

    printf("%s", lang->init_money_bye);
    return 0;
}
