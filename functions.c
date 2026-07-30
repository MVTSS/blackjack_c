#include <stdio.h>
#include <unistd.h>
#include "deck.h"
#include "term_functions.h"
#include "functions.h"
#include "player.h"

#define MENU_LIGNE_TITRE  1
#define MENU_LIGNE_MONEY  2
#define MENU_LIGNE_DECK   3
#define MENU_LIGNE_START  4
#define MENU_LIGNE_AIDE   5
#define MENU_LIGNE_QUIT   6
#define MENU_LIGNE_INPUT   8

#define INDICATION_LINE 10

#define DEALER_LINE 6
#define PLAYER_LINE 8

Player player;
Dealer dealer;

void init_display(int avail_money) {
    term_clear();
    term_move(MENU_LIGNE_TITRE,  1); printf("=== MATIS' BLACKJACK ===");
    term_move(MENU_LIGNE_MONEY,  1); printf("Argent disponible : %d$", avail_money);
}

void init_display_game(int avail_money, Deck* deck) {
    init_display(avail_money);
    term_move(MENU_LIGNE_DECK,  1); printf("Deck (%d cards left)\n", deck->nb_cards);
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
    init_display_game(*money, deck);

    //Card test_card = getRandomCard(deck);
    //char* cardString = toStringCard(test_card.value, test_card.suit);
    //printf("Took a card ! : (value : %d, suit : %d) and string form : %s", test_card.value, test_card.suit, cardString);
    //free(cardString);
     
    term_move(INDICATION_LINE,1); printf("Press enter to continue...");
    Card pulled_card = getRandomCard(deck);
    char* str_card = toStringCard(pulled_card.value, pulled_card.suit);
    term_move(DEALER_LINE,1); printf("Dealer : %s", str_card);
    wait_keypress();
    pulled_card = getRandomCard(deck);
    str_card = toStringCard(pulled_card.value, pulled_card.suit);
    term_move(PLAYER_LINE,1); printf("Player : %s", str_card);

    

    term_move(INDICATION_LINE,1); printf("Wanna play again fella ? (Y/n) : "); play_again = term_getchar();
    return play_again;
}

void start(int* money) {
    char play_again = 'y';
    int bet;
    Deck deck;
    createDeck(&deck);
    

    

    while (play_again != 'n' && deck.nb_cards > 45) {
        init_display_game(*money, &deck);
	    term_move(MENU_LIGNE_INPUT, 1); printf("How much do you wanna bet ? : ");
	    scanf("%d", &bet);

        if (bet > 0 && bet <= *money) {
            play_again = bj_round(&bet, money, &deck);
        }

        else { 
            printf("\nError : not enough money in bank, quitting\n"); sleep(2); play_again = 'n'; 
        }
    
    }

    if (play_again != 'n') {
	printf("\nSwitching deck, please wait...\n"); sleep(3);
	createDeck(&deck);
	start(money);
    }

}



