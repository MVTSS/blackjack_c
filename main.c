#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "term_functions.h"
#include "functions.h"
#include "save_load.h"

#define LIGNE_DEBUG_ERROR 10




int money;



void redirect(int signum) { // si Ctrl + C pour sortir
    if (signum == SIGINT) {
        term_clear();
        term_restore();
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






int main() {
    _init_signal();
    term_init();

    char *fname = "./blackjack_bank";
    load_encrypted(fname, &money);



    // while menu
    char selection;
    while (selection != 'q')
    {
        menu(&selection);
        term_move(LIGNE_DEBUG_ERROR, 1);
        // printf("DEBUG : char : %c\n", selection);

        switch (selection)
        {
        case 'H':
            help();
            term_clear();
            break;
        case 'S':
            // Start game
            break;
        default:
            puts("Commande inconnu, veuillez réessayer");
            break;
        }
    }

    redirect(SIGINT);
    return 0;
}
