#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "deck.h"

void init_display(int money);
void menu(char *selection, int avail_money);
void help(void);
void start(int* money);
char bj_round(int* round_bet, int* money, Deck* deck);
void add_card_dealer(Card c, char* str_cards, int* nb_cards_in_hand, int* nb_card_in_deck);

#endif
