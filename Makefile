all: main.c card.c player.c
	gcc -Wall main.c card.c player.c -o a.out