/*
 * InGame.h
 *
 *  Created by William Mann
 */


#ifndef INGAME_H_
#define INGAME_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <highscore.h>

typedef struct {
    char value;
    char color;
    int player;
    boolean trump;
}Cards;


Cards* createCards();


char* handString(Cards* hand);


/*
 * function hat gives the number of cards in an array
 * @param hand - array of cards you want the size of
 * @return an integer, the number of cards in the array
 */
int handSize(Cards* hand);


/*
 * Creates the players hand
 */
Cards* hand(Cards* cards, int size);


/*
 * Function that prints a card
 */
void cardPrint(char number, char color);


#endif /* INGAME_H_ */
