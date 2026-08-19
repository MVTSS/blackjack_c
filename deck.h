#ifndef DECK_H
#define DECK_H


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
} Card;

typedef struct {
    Card cards[52];
    int nb_cards;
} Deck;

void createDeck(Deck* deck);
void removeCard(Deck* deck, int index);
Card getRandomCard(Deck* deck);


// Since we get random cards already, there's not a use for shuffling the deck yet.
// Depends on the future implementation if we're rigorous.
//
//void shuffle_deck(Deck *deck);

char* toStringCard(int cardIdx, int suitIdx);
int isDeckEmpty(Deck* deck);

#endif
