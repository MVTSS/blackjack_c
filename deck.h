#ifndef TERM_H
#define TERM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum {
    heart,
    diamond,
    club,
    spade
} Suit;

typedef struct {
    int value;      
    int bj_value;
    Suit suit;
    int is_visible;
} Card;

typedef struct {
    Card cards[52];
    int nb_cards;
} Deck;

void createDeck(Deck *deck);
void turnCard(Card *carte);
Card getCard(Deck *deck);

void shuffle_deck(Deck *deck);

int isDeckEmpty(Deck *deck);

#endif
