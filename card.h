#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

typedef struct Card Card;

struct Card {
	int value;
	int points;
    int played;
};

Card* createCard(int value);
int compareCards(const void* a, const void* b);

#endif // CARD_H_INCLUDED