#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"

// Theorical max hand in blackjack ? When splitting (for Player)
// Theres the inital hand (let's say hand[0]), and when he splits you play "2 different hand" in the same round.
// We'll consider that you can't split a split, and for starters, we won't use it
#define MAX_HANDS 2

typedef struct {
    Card cards[12]; // Theorical max
    int nb_cards;
    // int bet;
} Hand;

typedef struct {

    // Association score/hand by index
    int score_per_hand;
    // int score_per_hand[MAX_HANDS];

    // int nb_hands;
    
    char hand_string[64];
    int nb_card_player;

    // Maybe useful when there will be multiplayer, depends on how to implement
    int money;
    int bet;
} Player;

typedef struct {
    int score_hand;
    char hand_string[64];
    int nb_card_dealer;
} Dealer; 

void addCard(Hand* hand, Card card);


#endif
