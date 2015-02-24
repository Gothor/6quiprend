#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "player.h"
#include "card.h"

#ifdef __unix__
    #define CLEAR_SCREEN system("clear")
#elif defined _WIN32
    #define CLEAR_SCREEN system("cls")
#endif

#define NB_CARDS (104)
#define NB_CARDS_HAND (10)

void nouvellePartie(Player** players); // Récupérer les informations sur les players
void nouvelleManche(Player** players, Card** cards); // Distribuer les cards et mettre en place l'aire de jeu

Card* chooseCard(Player* player); // Card choisie par le player (reel ou IA);

void shuffleCards(Card** cards, int nb) {
    Card* tmp;
    int i;
    
    srand(time(NULL));
    while (nb >= 2) {
        i = rand() % nb;
        tmp = cards[i];
        cards[i] = cards[nb - 1];
        cards[nb - 1] = tmp;
        nb--;
    }
}

void printBoard(Card** cards) {
    int i, j;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++)
            printf("+-----");
        printf("+\n");
        
        for (j = 0; j < 6; j++) {
            if (cards[i*6+j] != NULL)
                printf("| %3d ", cards[i * 6 + j]->value);
            else
                printf("|     ");
        }
        printf("|\n");
        
        for (j = 0; j < 6; j++) {
            if (cards[i*6+j] != NULL)
                printf("| %dpt ", cards[i * 6 + j]->points);
            else
                printf("|     ");
        }
        printf("|\n");
    }
    for (i = 0; i < 6; i++)
        printf("+-----");
    printf("+\n");
}

typedef struct Application Application;

struct Application {
    int nbPlayers;
    Player** players;
    Card** board;
    Card** cards;
};

Application* initApplication() {
    Application* app = malloc(sizeof(*app));
    int i;
	
    app->nbPlayers = 0;
    app->players = NULL;
    app->board = malloc(sizeof(*app->board) * 4 * 6);
	app->cards = malloc(sizeof(*app->cards) * NB_CARDS);
	for (i = 0; i < NB_CARDS; i++) {
	    app->cards[i] = createCard(i+1);
	}
    
    return app;
}

void freeApplication(Application* app) {
    int i;
    
    for (i = 0; i < app->nbPlayers; i++)
        freePlayer(app->players[i]);
    free(app->players);
    free(app->board);
    for (i = 0; i < NB_CARDS; i++)
        free(app->cards[i]);
    free(app->cards);
    free(app);
}

int newGame(Application* app) {
    int nbPlayers;
    int i, j;
    
    shuffleCards(app->cards, NB_CARDS);
    
    CLEAR_SCREEN;
	
	do {
	    printf("How may players ?\n");
	    scanf("%d", &nbPlayers);
	} while (nbPlayers < 2 || nbPlayers > NB_CARDS_HAND);
    app->nbPlayers = nbPlayers;
    
    app->players = malloc(sizeof(*app->players) * app->nbPlayers);
    for (i = 0; i < app->nbPlayers; i++) {
        app->players[i] = createPlayer("random", 0);
    }
    
    // Distribuer
    memset(app->board, 0, sizeof(*app->board) * 4 * 6);
    for (i = 0; i < 4; i++) {
        app->board[i * 6 + 0] = app->cards[i];
    }
    
    for (i = 0; i < app->nbPlayers; i++) {
        for (j = 0; j < NB_CARDS_HAND; j++) {
            playerAddCard(app->players[i], app->cards[i * NB_CARDS_HAND + j + 4]);
        }
        qsort(app->players[i]->cards, 10, sizeof(*app->players[i]->cards), compareCards);
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    int i;
    Application* app = initApplication();
    newGame(app);
    
    // nouvelle partie
    
    CLEAR_SCREEN;
    printBoard(app->board);
    printf("\n");
    
    for (i = 0; i < app->nbPlayers; i++)
        printPlayerCards(app->players[i]);
    
    freeApplication(app);

	return 0;
}
