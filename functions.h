#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "deck.h"


void init_display(int money);
void init_display_game(int avail_money, Deck* deck);
void menu(char *selection, int avail_money);
void help();
void update_deck_card_nb(int card_nb);
void add_card_entity(Card c, char* str_cards, int* nb_cards_in_hand);
// static maybe necessary for reset_round_state ? tbd
void reset_round_state(void);
char bj_round(int* round_bet, int* money, Deck* deck);
void start(int* money);

#endif
