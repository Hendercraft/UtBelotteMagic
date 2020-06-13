/*
 * menu.h
 *
 *  Created by William Mann
 */

#ifndef MAINMENU_MENU_H_
#define MAINMENU_MENU_H_


/*Libraries used*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <highscore.h>
#include <structures.h>

/******************************************************************************/
/**************************FUNCTIONS DEFINITION*******************************/
/****************************************************************************/

/*
 * This series of protocol is used to print in color, but it only works if we are on specified OS
 */
void magenta (int bold);
void reset();
void green(int bold);
void yellow(int bold);
void blue(int bold);
void red(int bold);
void cyan (int bold);


/*
 * Function thats prints the Programm's menu in ASCII art.
 */
void menuVisual();

/*
 * Function thats prints the Highscore's menu in ASCII art.
 */
void scoreVisual();

/*
 * Function that verifies if the is a number between 0 and n
 * @parameter b - integer min
 * @parameter n - integer max
 * @return a number
 */
int verify(int b,int n);

/*
 * Function to clear the cmd
 */
void clrscr();

/*
 * Function thats prints the ingame menu in ASCII art.
 * @param contract - the contract for this round
 * @param player - name of the player
 * @param falls - cards that have been played/cards in the fold
 * @param fallSize - size of the fold
 */
void ingameMenu(Bet contract, char* player, Player** table, Card** falls, int fallsSize);


/*
 * Function that transform a character of the color into the symbol
 * @param color - first letter of the color
 * @return the string of the character symbol
 */
char* colorToString(char color);

#endif /* MAINMENU_MENU_H_ */
