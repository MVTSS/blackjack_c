#include <stdio.h>
#include <unistd.h>
#include "deck.h"
#include "term_functions.h"
#include "functions.h"


#define MENU_LIGNE_TITRE  1
#define MENU_LIGNE_MONEY  2
#define MENU_LIGNE_START  4
#define MENU_LIGNE_AIDE   5
#define MENU_LIGNE_QUIT   6
#define MENU_LIGNE_INPUT   8



void init_display(int avail_money) {
    term_clear();
    term_move(MENU_LIGNE_TITRE,  1); printf("=== MATIS' BLACKJACK ===");
    term_move(MENU_LIGNE_MONEY,  1); printf("Argent disponible : %d$", avail_money);
}


void menu(char *selection, int avail_money) {
    term_move(MENU_LIGNE_TITRE,  1); printf("=== MATIS' BLACKJACK ===");
    term_move(MENU_LIGNE_MONEY,  1); printf("Argent disponible : %d$", avail_money);
    term_move(MENU_LIGNE_START, 1); printf("S: Commencer une partie");
    term_move(MENU_LIGNE_AIDE,   1); printf("H: Menu d'aide");
    term_move(MENU_LIGNE_QUIT,   1); printf("q: Quit");
    term_move(MENU_LIGNE_INPUT,   1); printf("Séléction : "); *selection = term_getchar();
    term_clear_line();
    term_flush();
}


void help(void) {
    term_clear();
    term_move(1,1); printf("=== RÈGLES DU BLACK JACK ===");
    term_move(2,1); printf("1. Blablabla bla");
    term_move(3,1); printf("blablablabla blablabla blabla blablabla");
    term_move(4,1); printf("blabla blablabla blablablablablabla blablabla blablabla blabla");
    term_move(5,1); printf("blablabla blablablabla blabla blablablabla blablabla blabla");
    term_move(6,1); printf("blablabla blablablabla blabla blabla blabla");
    term_move(7,1); printf("blablabla blablabla blabla blablablabla blablabla blabla");
    term_move(8,1); printf("blablabla blablablabla blabla blabla");
    term_move(9,1); printf("blablabla bla blablablabla blablabla blabla");
    term_move(11,1); printf("Appuyer sur entrer pour retourner au menu...");
    wait_keypress();
    term_clear();
}


char bj_round(int* round_bet, int* money, Deck* deck) {
    char play_again;
    *money -= *round_bet;
    term_clear();
    init_display(*money);

    // Game...
    printf("\nGAME\n");
    printf("Deck (%d cards left)\n", deck->nb_cards);
    Card test_card = getRandomCard(deck);
    printf("Took a card ! : (value : %d, suit : %d)", test_card.value, test_card.suit);
    wait_keypress();

    printf("Wanna play again fella ? (Y/n) : "); play_again = term_getchar();
    return play_again;
}

void start(int* money) {
    char play_again = 'y';
    int bet;
    Deck deck;
    createDeck(&deck);

    init_display(*money);

    while (play_again != 'n') {
	term_move(MENU_LIGNE_INPUT, 1); printf("How much do you wanna bet ? : ");
	scanf("%d", &bet);

    if (bet > 0 && bet <= *money)
	    play_again = bj_round(&bet, money, &deck);
    else { 
	printf("\nError : not enough money in bank, quitting\n"); sleep(2); play_again = 'n'; 
    }
    
    }
}



