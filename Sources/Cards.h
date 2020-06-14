#ifndef CARDS_H
#define CARDS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <structures.h>
#include <menu.h>

/******************************************************************************/
/**************************FUNCTIONS DEFINITION*******************************/
/****************************************************************************/

/**
 * This function manages a turn of the game.
 * @param table - The array containing the address of each player of the game.
 * @param gamebet -  The current bet.
 * @param playname -  A string containing the name of the play, used for the interface.
 * @param playerid -  The ID of the player who will play the first card.
 * @param ItstheTHcard - The card that will be played when playcard is called: it's initialised as 1 in the main, and will
 * finish at 32
 * @return The ID of the player who won has this turn, any will return -1 if there's any memory error.
 */
int turn(Player** table,Bet gamebet,char* playname,int playerid,int* ItstheTHcard);


/**
 * This function goes through the falls and count the number of trumps in it.
 * If there's any, it will modify the int passed as its 3rd parameter according to the number of trumps.
 * @param falls -  An array of pointers on Card containing all the Cards that have been played this round.
 * @param sizefalls -  The size of the fall.
 * @param nbxtrump - Expects a pointer on a int, it will be modified if any trump has been found.
 * @return - An array of pointers on Card containing all the trumps of the falls.
 */
Card** anytrump(Card** falls,int sizefalls,int* nbxtrump);


/**
 * This function will go through the hand of a given player and will return an array containing the index of the card that he can play.
 * @param table - The array containing the address of each Player of the game.
 * @param falls - An array of pointers of Card containing all the Cards that have been played this round.
 * @param playerid - The id of the player whose hand we'll go through.
 * @param sizefalls - The current size of the fall.
 * @param outputsize - A pointer where the size of the returned array will be given.
 * @return an array of int - This array will contain the index of each playable card.
 */
int* checkcard(Player** table,Card** falls ,int playerid,int sizefalls,int* outputsize);

/**
 * This function go through the Cards playable by an IA and will choose the best one.
 * @param table - The array containing the memory address of each Player in the game.
 * @param falls - An array of pointers of Card containing all the Cards that have been played this round.
 * @param playerid - The id of IA who is going to play.
 * @param sizefalls - The current size of the fall.
 * @param allowedcard - An array containing all of the allowed cards.
 * @param sizeallowedcard - The size of the so named array.
 * @return int - The index of the card the IA is going to play.
 */
int IAcompute(Player** table, Card** falls,int playerid,int sizefalls,int* allowedcard,int sizeallowedcard);


/**
 * This function will take a card that has already been tested from the hand of a player
 * and adds it to the current fall; it will call removecard to remove the pointer to the Card from the hand of the player
 * @param table - The array containing the address of each Player of the game.
 * @param falls - An array of pointer on Card containing all the Cards that have been played this round.
 * @param playerid - The ID of the player who wishes to play.
 * @param cardid - The ID of the card he wishes to play.
 * @param sizefalls - A pointer on the current size of the falls.
 * @param newposition - The Card position in the future game; this corresponds to the order in which this card is played.
 * @return the modifed falls.
 */
Card** playcard(Player** table,Card** falls,int playerid,int cardid,int* sizefalls,int* newposition);
/**
 * This will deal the cards to each player
 * @param table - The array containing the memory address of each Player of the game.
 * @param deck - The array containing the memory address of each Card of the game.
 * @param dealerid - The id of the player who is dealing the cards this game.
 */
void cardsdeal(Player** table,Card** deck,int dealerid);
/**
 * This function will parse through the deck and set the trump value of the selected color to TRUE.
 * @param deck - The array containing the memory address of each Card of the game.
 * @param trump - The color that will become the trump.
 */
void definetrump(Card** deck,char trump);

/**
 * This function generates and returns an array containing all player data.
 * Player 1 (South) is the user, he's teaming with Player 3 (North AI).
 * The other Player 2 (West AI) and  Player 4 (East AI) are together.
 * @return an array of 4 pointers on Player.
 */
Player** createplayer();

/**
 * This function generates and returns the set of 32 cards that will be used during the game.
 * In order to avoid copying Cards into players hand, we'll be manipulating pointers.
 * @return an array of 32 pointers on Card, their player value is set to 0 by default.
 */
Card** createcards();


/**
  * This function will be called in End of turn if at least one trump has been played.
  * it will look through the array and return the id of the player who has won the turn.
  * @param fallstrump - An array of pointer on Card containing all the trumps that have been played.
  * @param size - the size of the passed array
  * @param max - The value of the strongest trump, used in checkcard mostly
  * @return a int containing the id of the winning player
*/
int whowintrump(Card** fallstrump,int size,int* max);

/**
  * This function will be called each End of turn if no trump has been played.
  * it will look through the array and return the id of the player who has won the turn.
  * @param falls - An array of pointers on Card containing all the Cards that have been played this round.
  * @param sizefalls - The actual size of the fall.
  * @param max - The value of the strongest Card, used in AIcompute mostly.
  * @return a int containing the id of the winning player.
*/
int whowin(Card** falls,int sizefalls,int* max);

/**
 * This function will be launched once everybody has played a card.
 * Its role is to modify the card.player value, setting it to the -1,-2,-3 or -4 depending on which player has won.
 * It uses anytrump to count the trump in the fall.
 * whowin and whowintrump are used to determine the id of the winning player.
 * @param falls - The address of the cards that have been played by each player.
 * @return a int containing the id of the winning player or -1 if there's a memory allocation error.
 */
int Endofturn(Card** falls);

/**
 * This function goes through the hand of a given player and removes a pointer from it.
 * It will then realloc the hand with its new size.
 * @param table - An array of pointer on player.
 * @prama playerid - The ID of the player whose hand we'll resize.
 * @param index - The index of the card we wish to remove.
 * @return A Boolean - TRUE if there's no memory error, FALSE otherwise.
 */
Boolean removecardsfromhand(Player** table,int playerid,int index);

/**
 * This function goes trough an array of pointer of Card.
 * It will give the index of the lowest card superior to the 3rd parameter.
 * It will ignore Cards that are trump.
 * @param cardarray - An array of pointer on Card.
 * @prama size - The size of the array of card.
 * @param supp - The value the returned card is supposed to be superior to.
 * @return the index of lowest card.
 */
int mincard(Card** cardarray,int size,int supp);

/**
 * This function goes trough an array of pointer of Card.
 * It will give the index of the lowest card superior to the 3rd parameter.
 * the 3rd parameter MUST BE ALREADY CONVERTED IN TRUMP VALUE !
 * It exept to work with trump.
 * @param cardarray - An array of pointer on Card.
 * @prama size - The size of the array of card.
 * @param supp - The value the returned card is supposed to be superior to.
 * @return the index of lowest card.
 */
int mintrump(Card** cardarray,int size,int supp);

/**
 * This funtion goes through the deck and shuffles it.
 * @param deck - The array of pointer on Card containing all the Card of the game .
 * @prama cutfrom - where to cut the array.
 */
void shuffle(Card** deck,int cutfrom);



#endif

