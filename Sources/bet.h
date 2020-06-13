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
#include <highscore.h>


/*
 * Displays the bet menu for the player
 */
Bet betMenu(Player** table, Bet previousChoice);


Bet botBet(Player** table, Bet previousChoice, int botNb);

/*
 * Function that gives the number of strong card in a hand
 * @param cardColorValues - array of the values of all the card of one color
 * @param trump - the color a trump or not.
 * @return an integer representing the number of strong card from that color
 */
int howManyStrong(int* cardColorValues, int size, Boolean trump);


#endif /* MAINMENU_BET_H_ */
