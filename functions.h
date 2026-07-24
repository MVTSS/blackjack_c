#ifndef FUNC_H
#define FUNC_H

#include "deck.h"

void init_display(int money);
void menu(char *selection, int avail_money);
void help(void);
void start(int* money);
char bj_round(int* round_bet, int* money, Deck* deck);

#endif
