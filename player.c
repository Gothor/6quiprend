#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"

Player* createPlayer(const char* name, int ai) {
    Player* player = malloc(sizeof(*player));
    
    player->name = strdup(name);
    player->ai = ai;
    player->nbCards = 0;
    player->cards = malloc(sizeof(*player->cards) * 10);
    memset(player->cards, 0, 10 * sizeof(*player->cards));
    
    return player;
}

void playerAddCard(Player* player, Card* card) {
    int i;
    
    if (!player || !card)
        return ;
    
    if (player->nbCards >= 10)
        return ;
    
    for (i = 0; i < player->nbCards; i++)
        if (compareCards(player->cards[i], card) == 0)
            return ;
    
    player->cards[player->nbCards] = card;
    player->nbCards++;
}

void playerRemoveCard(Player* player, int value) {
    int i;
    
    if (!player)
        return ;
    
    for (i = 0; i < player->nbCards; i++)
        if (player->cards[i]->value == value) {
            player->cards[i] = NULL;
            player->nbCards--;
        }
}

void printPlayerCards(Player* player) {
    int i;
    
    if (!player)
        return ;
    
    printf("Main de %s :\n", player->name);
    for (i = 0; i < player->nbCards; i++)
        printf("+-----");
    printf("+\n");
    
    for (i = 0; i < 10; i++) {
        if (player->cards[i])
            printf("| %3d ", player->cards[i]->value);
    }
    printf("|\n");
    
    for (i = 0; i < 10; i++) {
        if (player->cards[i])
            printf("| %dpt ", player->cards[i]->points);
    }
    printf("|\n");
    
    for (i = 0; i < player->nbCards; i++)
        printf("+-----");
    printf("+\n");
}

void freePlayer(Player* player) {
    if (!player)
        return ;
    
    free(player->name);
    free(player->cards);
    free(player);
}