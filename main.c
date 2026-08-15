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

int money = 100;

void redirect(int signum) { // if Ctrl + C to leave
    if (signum == SIGINT) {
        Language_Pack* lang = get_language_pack();
        term_clear();
        term_restore();
        save_encrypted("./blackjack_bank", &money, sizeof(money));
        printf(lang->menu_early_leave, money);
        puts(lang->menu_bye);
        exit(0);
    }
}

void _init_signal(void) {
    // Init signal
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler = redirect;
    sigaction(SIGINT,&act,NULL);
}

int main() {
    _init_signal();
    srand(time(NULL));
    
    init_languages();
    load_config();
    set_language(get_language_from_config());

    char *fname = "./blackjack_bank";

    if (!load_encrypted(fname, &money)) {
        Language_Pack* lang = get_language_pack();
        printf("%s", lang->error_cant_load_file);
        term_flush();
        return 1;
    }

    // while menu
    char selection = '\0';
    while (selection != 'q')
    {
        set_language(get_language_from_config());
        Language_Pack* lang = get_language_pack();
        term_init();
        menu(&selection, money);

        switch (selection)
        {
        case 'H':
        case 'h':
            help();
            break;
        case 'S':
        case 's':
            start(&money);
            break;
        case 'L':
        case 'l':
            menu_lang();
            break;
        case 'Q':
        case 'q':
            break;
        default:
            printf("%s", lang->game_unknown_command);
            break;
        }
    }

    term_restore();
    save_encrypted(fname, &money, sizeof(money));

    Language_Pack* lang = get_language_pack();
    printf(lang->menu_early_leave, money);
    puts(lang->menu_bye);

    cleanup_languages();
    cleanup_config();
    return 0;
}
