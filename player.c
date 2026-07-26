#include "player.h"

void addCard(Hand* hand, Card card) {
    hand->cards[hand->nb_cards] = card;
    hand->nb_cards++;
}
