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
#include <structures.h>

/*
 * Displays the bet menu for the player
 * @param table - dynamic array of players with their hand, hand size, etc.
 * @param previousChoice - bet type the previous bet with the contract, the team who made it, the value and if it is coinched or surcoinched
 * @return the new bat made by the player
 */
Bet betMenu(Player** table, Bet previousChoice);


/*
 * Makes the bet for the bots
 * @param table - dynamic array of players with their hand, hand size, etc.
 * @param previousChoice - bet type the previous bet with the contract, the team who made it, the value and if it is coinched or surcoinched
 * @param botNb - number of the bot who is betting
 * @return the new bat made by the player
 */
Bet botBet(Player** table, Bet previousChoice, int botNb);


/*
 * Function that gives the number of strong card in a hand (for trumps)
 * @param cardColorValues - array of the values of all the card of one color
 * @param trump - the color a trump or not.
 * @return an integer representing the number of strong card from that color
 */
int howManyStrong(int* cardColorValues, int size, Boolean trump);


#endif /* MAINMENU_BET_H_ */
