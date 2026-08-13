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

#define WHATTODO_LINE 10
#define INDICATION_LINE 12


#define DECK_LINE 3
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
    int input;

    term_move(MENU_LIGNE_TITRE,  1); printf("=== MATIS' BLACKJACK ===");
    term_move(MENU_LIGNE_MONEY,  1); printf("Argent disponible : %d$", avail_money);
    term_move(MENU_LIGNE_START, 1); printf("S: Commencer une partie");
    term_move(MENU_LIGNE_AIDE,   1); printf("H: Menu d'aide");
    term_move(MENU_LIGNE_QUIT,   1); printf("q: Quit");

    do {
        term_move(MENU_LIGNE_INPUT, 1);
        printf("Selection : ");
        term_flush();
        input = getchar();
        while (input == '\n' || input == '\r') {
            input = getchar();
        }
    } while (input == EOF);

    *selection = (char)input;
    term_clear_actual_line();
    term_flush();
}


void help(void) {
    term_clear();
    term_move(1,1); printf("=== RÈGLES DU BLACK JACK ===\n");
    printf("1. Blablabla bla\n");
    printf("blablablabla blablabla blabla blablabla\n");
    printf("blabla blablabla blablablablablabla blablabla blablabla blabla\n");
    printf("blablabla blablablabla blabla blablablabla blablabla blabla\n");
    printf("blablabla blablablabla blabla blabla blabla\n");
    printf("blablabla blablabla blabla blablablabla blablabla blabla\n");
    printf("blablabla blablablabla blabla blabla\n");
    printf("blablabla bla blablablabla blablabla blabla\n");
    printf("\nAppuyer sur entrer pour retourner au menu...\n");
    wait_keypress();
    term_clear();
}


void update_deck_card_nb(int card_nb) {
    term_move(DECK_LINE,  1); printf("\nDeck (%d cards left)\n", card_nb);
}

void add_card_entity(Card c, char* str_cards, int* nb_cards_in_hand) {
    if (*nb_cards_in_hand == 0) {
        strcat(str_cards, toStringCard(c.value, c.suit));
    } else {
        strcat(str_cards, ", ");
        strcat(str_cards, toStringCard(c.value, c.suit));
    }

    (*nb_cards_in_hand)++;
    printf("%s\r", str_cards);
}


char dealer_cards[64] = "Dealer : ";
int nb_dealer_card = 0;
char player_cards[64] = "Player : ";
int nb_player_card = 0;

static void reset_round_state(void) {
    snprintf(dealer_cards, sizeof(dealer_cards), "Dealer : ");
    snprintf(player_cards, sizeof(player_cards), "Player : ");
    nb_dealer_card = 0;
    nb_player_card = 0;
}

char bj_round(int* round_bet, int* money, Deck* deck) {
    char play_again;  
    char move;
    reset_round_state();
    *money -= *round_bet;
    term_clear();
    init_display(*money);
    update_deck_card_nb(deck->nb_cards);
    //Card test_card = getRandomCard(deck);
    //char* cardString = toStringCard(test_card.value, test_card.suit);
    //printf("Took a card ! : (value : %d, suit : %d) and string form : %s", test_card.value, test_card.suit, cardString);
    //free(cardString);
     
    term_move(INDICATION_LINE,1); printf("Press enter to continue...");
    // Dealer turns
    Card pulled_card = getRandomCard(deck);
    term_move(DEALER_LINE,1);
    add_card_entity(pulled_card, dealer_cards, &nb_dealer_card);
    update_deck_card_nb(deck->nb_cards);
    
    wait_keypress();

    pulled_card = getRandomCard(deck);
    term_move(PLAYER_LINE,1);
    add_card_entity(pulled_card, player_cards, &nb_player_card);
    update_deck_card_nb(deck->nb_cards);

    wait_keypress();

    pulled_card = getRandomCard(deck);
    term_move(PLAYER_LINE,1);
    add_card_entity(pulled_card, player_cards, &nb_player_card);
    update_deck_card_nb(deck->nb_cards);


    term_move(WHATTODO_LINE,1);
    printf("\nWHAT TO DO ? (H)it, (C)heck : "); move = term_getchar();
    while (move == 'H')
    {
        term_clear_line(WHATTODO_LINE);
        wait_keypress();
        pulled_card = getRandomCard(deck);
        term_move(PLAYER_LINE,1);
        add_card_entity(pulled_card, player_cards, &nb_player_card);
        update_deck_card_nb(deck->nb_cards);
        term_move(WHATTODO_LINE,1);
        printf("\nWHAT TO DO ? (H)it, (C)heck : "); move = term_getchar();
    }
    


    

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



