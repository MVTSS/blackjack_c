#define _POSIX_C_SOURCE 200809L // Pour enlever les erreurs avec sigaction incomplet
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "save_load.h"



void redirect(int signum) { // si Ctrl + C pour sortir
    if (signum == SIGINT) {
        puts("\nAlright as you want, see ya !");
        exit(0);
    }
}



int main() {
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
            printf("Your bank already exists, but seems empty... you poor bastard.\n Would you like to fill it with 100 WHOLE DOLLARS ? (y/n)\n-> ");
        } else
        {
            printf("File already exists but there's money on it...\n");
            contain_data = 1;
        }
        

    } else {
        printf("Your bank doesn't exist... Should we create it and add 100 dollars ? (y/n)\n-> ");
    }


    char ans;


    if (contain_data)
    {
        load_encrypted(fname, &loaded_money);
        printf("There's %d$ in your bank (that's... good). \nWe can reset it, if you want... would you like to add those juicy 100$ instead ? (y/n)\n-> ", loaded_money);
    }
    

    scanf("%c", &ans);
    puts("");
    switch (ans)
    {
    case 'Y':
    case 'y':
        printf("We'll go bankrupt with this one...\n");
        save_encrypted(fname, &init_money, sizeof(init_money));
        load_encrypted(fname, &loaded_money);
        printf("-- %d$ in your blackjack bank\n", loaded_money);
        break;
    
    default:
        puts("You're call...");
        puts("-- Money NOT added");
        break;
    }

    puts("See you !");
    return 0;
}