#define _POSIX_C_SOURCE 200809L // Pour enlever les erreurs avec sigaction incomplet
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "term_functions.h"
#include "functions.h"
#include "save_load.h"
#include "language.h"
#include "config.h"

#define LIGNE_DEBUG_ERROR 10




int money = 100;

void redirect(int signum) { // si Ctrl + C pour sortir
    if (signum == SIGINT) {
        term_clear();
        term_restore();
        save_encrypted("./blackjack_bank", &money, sizeof(money));
        printf("Money in bank : %d$\n", money);
        puts("See you soon !");
        exit(0);
    }
}




void _init_signal(void) {
    // Init signals
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler = redirect;
    sigaction(SIGINT,&act,NULL);
}


void start_game(void) {
    start(&money);

}



int main() {
    _init_signal();
    srand(time(NULL));
    
    init_languages();
    load_config();
    set_language(get_language_from_config());

    char *fname = "./blackjack_bank";
    if (!load_encrypted(fname, &money)) {
        money = 100;
    }

    // while menu
    char selection = '\0';
    while (selection != 'q')
    {
        term_init();
        menu(&selection, money);
        term_move(LIGNE_DEBUG_ERROR, 1);
        printf("DEBUG : char : %c\n", selection);

        switch (selection)
        {
        case 'H':
        case 'h':
            help();
            break;
        case 'S':
        case 's':
            start_game();
            break;
        case 'L':
        case 'l':
            menu_lang();
            break;
        case 'q':
            break;
        default:
            Language_Pack* lang = get_language_pack();
            puts(lang->game_unknown_command);
            break;
        }
    }

    term_restore();
    save_encrypted(fname, &money, sizeof(money));
    cleanup_languages();
    cleanup_config();
    return 0;
}
