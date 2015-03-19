#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "card.h"

typedef struct Player Player;

struct Player {
    char* name;
    int ai;
    int nbCards;
    Card** cards;
    int score;
};

Player* createPlayer(const char* name, int ai);
void printPlayerCards(Player* player);
void playerAddCard(Player* player, Card* card);
void playerRemoveCard(Player* player, int value);
void freePlayer(Player* player);

#endif // PLAYER_H_INCLUDED