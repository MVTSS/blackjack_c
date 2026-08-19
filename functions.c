#include "term_functions.h"
#include "functions.h"
#include "player.h"
#include "language.h"

#define MENU_LIGNE_TITRE   1
#define MENU_LIGNE_MONEY   2
#define MENU_LIGNE_DECK    3
#define MENU_LIGNE_START   4
#define MENU_LIGNE_AIDE    5
#define MENU_LIGNE_QUIT    6
#define MENU_LIGNE_LANG    7
#define MENU_LIGNE_INPUT   9



#define WHATTODO_LINE   10
#define INDICATION_LINE 12


#define DECK_LINE   3
#define DEALER_LINE 6
#define PLAYER_LINE 8

Player player1;
Dealer dealer;


void init_display(int avail_money) {
    term_clear();
    Language_Pack* lang = get_language_pack();
    term_move(MENU_LIGNE_TITRE,  1); printf("%s", lang->menu_title);
    term_move(MENU_LIGNE_MONEY,  1); printf(lang->menu_available_money, avail_money);
}

void init_display_game(int avail_money, Deck* deck) {
    init_display(avail_money);
    update_deck_card_nb(deck->nb_cards);
}


void menu(char *selection, int avail_money) {
    int input;
    Language_Pack* lang = get_language_pack();

    term_move(MENU_LIGNE_TITRE,  1); printf("%s", lang->menu_title);
    term_move(MENU_LIGNE_MONEY,  1); printf(lang->menu_available_money, avail_money);
    term_move(MENU_LIGNE_START,  1); printf("%s", lang->menu_start_game);
    term_move(MENU_LIGNE_AIDE,   1); printf("%s", lang->menu_help);
    term_move(MENU_LIGNE_QUIT,   1); printf("%s", lang->menu_quit);
    term_move(MENU_LIGNE_LANG,   1); printf("%s", lang->menu_change_lang);

    do {
        term_move(MENU_LIGNE_INPUT, 1);
        printf("%s", lang->menu_selection);
        term_flush();
        input = getchar();
        while (input == '\n' || input == '\r') {
            term_move(MENU_LIGNE_INPUT, 1);
            printf("%s", lang->menu_selection);
            term_flush();
            input = getchar();
        }
    } while (input == EOF);

    *selection = (char)input;
    term_clear_actual_line();
    term_flush();
}


void help() {
    term_clear();
    Language_Pack* lang = get_language_pack();
    term_move(1,1); printf("%s\n", lang->help_title);
    printf("%s\n", lang->help_rules_line1);
    printf("\n%s", lang->help_press_enter);
    term_flush();
    getchar(); getchar();
    term_clear();
}


void update_deck_card_nb(int card_nb) {
    Language_Pack* lang = get_language_pack();
    term_move(DECK_LINE, 1); printf(lang->game_deck_info, card_nb);
}

void add_card_entity(Card c, char* str_cards, int* nb_cards_in_hand, int* score) {
    if (*nb_cards_in_hand == 0) {
        strcat(str_cards, toStringCard(c.value, c.suit));
    } else {
        strcat(str_cards, ", ");
        strcat(str_cards, toStringCard(c.value, c.suit));
    }

    (*nb_cards_in_hand)++;

    (*score) += c.bj_value;

    printf("%s (%d)\r", str_cards, *score);
}




void reset_round_state(void) {
    Language_Pack* lang = get_language_pack();
    snprintf(dealer.hand_string, sizeof(dealer.hand_string), "%s", lang->game_dealer);
    snprintf(player1.hand_string, sizeof(player1.hand_string), "%s", lang->game_player);
    player1.score_per_hand = 0;
    dealer.score_hand = 0;
    player1.nb_card_player = 0;
    dealer.nb_card_dealer = 0;
}

char bj_round(int* round_bet, int* money, Deck* deck) {
    char play_again;  
    char move;
    Language_Pack* lang = get_language_pack();
    reset_round_state();
    *money -= *round_bet;
    term_clear();
    init_display(*money);
    update_deck_card_nb(deck->nb_cards);
     
    term_move(INDICATION_LINE,1); printf("%s", lang->game_press_enter);
    term_flush();

    // Dealers turn
    Card pulled_card = getRandomCard(deck);
    term_move(DEALER_LINE,1);
    add_card_entity(pulled_card, dealer.hand_string, &dealer.nb_card_dealer, &dealer.score_hand);
    update_deck_card_nb(deck->nb_cards);
    
    term_getchar();

    pulled_card = getRandomCard(deck);
    term_move(PLAYER_LINE,1);
    add_card_entity(pulled_card, player1.hand_string, &player1.nb_card_player, &player1.score_per_hand);
    update_deck_card_nb(deck->nb_cards);

    term_getchar();

    pulled_card = getRandomCard(deck);
    term_move(PLAYER_LINE,1);
    add_card_entity(pulled_card, player1.hand_string, &player1.nb_card_player, &player1.score_per_hand);
    update_deck_card_nb(deck->nb_cards);


    term_move(WHATTODO_LINE,1);
    printf("%s", lang->game_what_to_do); move = term_getchar();
    while (move == 'H' && deck->nb_cards > 7 && player1.score_per_hand < 21)
    {
        term_clear_line(WHATTODO_LINE);
        wait_keypress();
        pulled_card = getRandomCard(deck);
        term_move(PLAYER_LINE,1);
        add_card_entity(pulled_card, player1.hand_string, &player1.nb_card_player, &player1.score_per_hand);
        update_deck_card_nb(deck->nb_cards);
        if (player1.score_per_hand > 21) {
            term_clear_line(WHATTODO_LINE);
            term_clear_line(INDICATION_LINE);
            term_move(INDICATION_LINE, 1);
            printf("Score too high ! You lost");
            term_flush();
            sleep(2);
            break;
        }
        term_move(WHATTODO_LINE,1);
        printf("%s", lang->game_what_to_do); move = term_getchar();
    }



    term_move(INDICATION_LINE,1); printf("%s", lang->game_play_again); play_again = term_getchar();
    return play_again;
}

void start(int* money) {
    char play_again = 'y';
    int bet;
    Deck deck;

    createDeck(&deck);

    while (play_again != 'n' && deck.nb_cards > 45) {
        Language_Pack* lang = get_language_pack();
        init_display_game(*money, &deck);
        term_move(MENU_LIGNE_INPUT, 1); printf("%s", lang->game_how_much_bet);
        term_flush();
        scanf("%d", &bet);
        wait_keypress();

        if (bet > 0 && bet <= *money) {
            play_again = bj_round(&bet, money, &deck);
        }
        else { 
            Language_Pack* lang = get_language_pack();
            printf("\n%s", lang->game_error_not_enough_money);
            term_flush();
            sleep(2);
            play_again = 'n'; 
        }
    }

    if (play_again != 'n') {
        Language_Pack* lang = get_language_pack();
        printf("\n%s", lang->game_switching_deck);
        term_flush();
        sleep(3);
        createDeck(&deck);
        start(money);
    }
}



