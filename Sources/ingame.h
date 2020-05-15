/*
 * InGame.h
 *
 *  Created by William Mann
 */


#ifndef MAINMENU_INGAME_H_
#define MAINMENU_INGAME_H_


#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char value
    char* color
    int player
    Boolean trump
}Cards


/*
 * Prints the cards in the player's hand
 */
void handPrint(Cards* Cards, int size);


/*
 * Function that prints a card
 */
void cardPrint(char number, char color);


#endif /* MAINMENU_INGAME_H_ */
