#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FALSE = 0,
    TRUE = 1
}Boolean;

typedef struct {
    int value;
    char color;
    int player;
    Boolean trump;
}Card;

typedef struct{
	Card* Hand;
	int id;
	int bet;
	int hand_size;
}Player;

/*This fonction generate and retrun a array of Cards,already
 set to their value*/
Card* creatcards();


Card* WhoWins(Card* falls);
