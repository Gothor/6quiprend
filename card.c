#include <stdlib.h>
#include "card.h"

Card* createCard(int value) {
    Card* card = malloc(sizeof(*card));
    
    card->value = value;
    if (value == 55)
        card->points = 7;
    else if (value % 11 == 0)
        card->points = 5;
    else if (value % 10 == 0)
        card->points = 3;
    else if (value % 5 == 0)
        card->points = 2;
    else
        card->points = 1;
    card->played = 0;
    
    return card;
}

int compareCards(const void* a, const void* b) {
    Card *cardA = (Card*) a,
        *cardB = (Card*) b;
        
    if (cardA->value < cardB->value)
        return -1;
    if (cardA->value > cardB->value)
        return 1;
    return 0;
}