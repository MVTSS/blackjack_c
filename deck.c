#include <stdlib.h>
#include "deck.h"

void createDeck(Deck *deck) {
    int index = 0;

    deck->nb_cards = 52;

    for (Suit suit = heart; suit <= spade; suit++) {
        for (int value = 1; value <= 13; value++) {
            deck->cards[index].value = value;

            if (value == 1)
                deck->cards[index].bj_value = 11;
            else if (value >= 10)
                deck->cards[index].bj_value = 10;
            else
                deck->cards[index].bj_value = value;

            deck->cards[index].suit = suit;
            deck->cards[index].is_visible = 0;

            index++;
        }
    }
}


void turnCard(Card *carte) {
    carte->is_visible = !carte->is_visible;
}

void removeCard(Deck *deck, int index) {
    // Décaler toutes les cartes après l'index
    for (int i = index; i < deck->nb_cards - 1; i++) {
        deck->cards[i] = deck->cards[i + 1];
    }

    deck->nb_cards--;
}


Card getRandomCard(Deck *deck) {
    Card to_get;
    int randCardIdx = (rand() % (deck->nb_cards));
    
    to_get = deck->cards[randCardIdx];
    removeCard(deck, randCardIdx);
    

    return to_get;
}

int isDeckEmpty(Deck *deck) {
    return deck->nb_cards == 0;
}

