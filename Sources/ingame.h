/*
 * InGame.h
 *
 *  Created by William Mann
 */


#ifndef INGAME_H_
#define INGAME_H_


#include <stdio.h>
#include <stdlib.h>
#include <highscore.h>

typedef struct {
    char value;
    char color;
    int player;
    boolean trump;
}Cards;


Cards* createCards();


/*
 * Prints the cards in the player's hand
 */
void handPrint(Cards* cards, int size);


/*
 * Function that prints a card
 */
void cardPrint(char number, char color);


#endif /* INGAME_H_ */
