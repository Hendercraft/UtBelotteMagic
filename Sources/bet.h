/*
 * bet.h
 *
 *  Created by William Mann
 */

#ifndef MAINMENU_BET_H_
#define MAINMENU_BET_H_

#include <menu.h>
#include <Cards.h>
#include <stdlib.h>
#include <stdio.h>


/* Creation of structure composed of: */
typedef struct {
	int contract; /*an integer for the chosen contract. 1 is N points, 2 capot, 3 generale, 4 coinche and 5 surcoinche. 0 is no contract*/
	int points; /*an integer for the points that the contract gives*/
	char trump; /*a character for the color of the trump + t for all trump and n for no trump*/
} bet;


/*
 * Displays the bet menu for the player
 */
bet betMenu(Player** table, bet previousChoice);


bet botBet(Player** table, bet previousChoice, int botNb);

/*
 * Function that gives the number of strong card in a hand
 * @param cardColorValues - array of the values of all the card of one color
 * @param trump - the color a trump or not.
 * @return an integer representing the number of strong card from that color
 */
int howManyStrong(int* cardColorValues, int size, boolean trump);


#endif /* MAINMENU_BET_H_ */
