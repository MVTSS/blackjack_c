#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"

// Theorical max hand in blackjack ? When splitting (for Player)
// Theres the inital hand (let's say hand[0]), and when he splits you play "2 different hand" in the same round.
// We'll consider that you can't split a split
#define MAX_HANDS 2

typedef struct {
    Card cards[12]; // max théorique
    int nb_cards;
    int bet;
} Hand;

typedef struct {
    Hand hands[MAX_HANDS];
    int nb_hands;

    // Maybe useful when there will be multiplayer, depends on how to implement
    int money;
} Player;

typedef struct {
    Hand hand;
} Dealer; 

void addCard(Hand* hand, Card card);


#endif
