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
 * This function manage a trun of the game .
 * If there is any it will modify the int passed has its 3rd parameter accoding to the number of trump
 * @param table - The array contening the adress of each Player of the game.
 * @param gamebet -  The current bet.
 * @param playname -  A string contening the name oft he play, used for the interface.
 * @param playerid -  The id of the player who play the first card.
 * @param ItstheTHcard - The card that will be played when playcard is called : Is initialised as 1 in the main, sould
 * finsh at 32
 * @return The ID of the player who won or -1 if there's any memorry error.
 */
int turn(Player** table,Bet gamebet,char* playname,int playerid,int* ItstheTHcard);


/**
 * This function go trought the falls and count the number of trump.
 * If there is any it will modify the int passed has its 3rd parameter accoding to the number of trump
 * @param falls -  An array of pointer on Card contening all the Cards that have been played this round.
 * @param sizefalls -  the size of the fall.
 * @param nbxtrump - expect a pointer on a int, it will be modify if anytrump has been found.
 * @return An array of pointer on Card contening all the trump of the falls.
 */
Card** anytrump(Card** falls,int sizefalls,int* nbxtrump);


/**
 * This function will go trought the hand of a given player and retrun an array contening the index of the card he can play.
 * @param table - The array contening the adress of each Player of the game.
 * @param falls - An array of pointer on Card contening all the Cards that have been played this round.
 * @param playerid - The id of the player which hand we'll go trought.
 * @param sizefalls - The current size of the fall.
 * @param outputsize - A pointer where the size of the returned array will be given.
 * @return an array of int - This array will containt the index of each playedable card.
 */
int* checkcard(Player** table,Card** falls ,int playerid,int sizefalls,int* outputsize);

/**
 * This function go trought the Cards playable by an IA and will choose the best.
 * @param table - The array contening the adress of each Player of the game.
 * @param falls - An array of pointer on Card contening all the Cards that have been played this round.
 * @param playerid - The id of IA who wants to play.
 * @param sizefalls - The current size of the fall.
 * @param allowedcard - A array contening all the allowed card.
 * @param sizeallowedcard - The size of t                            cardPlayed = playcard(table,falls,1,playedCard,&size,&numberCardsPlayed);he so named array.
 * @return a int - The index of the car the IA is going to play.
 */
int IAcompute(Player** table, Card** falls,int playerid,int sizefalls,int* allowedcard,int sizeallowedcard);


/**
 * This function will take a card that has already been tested from the hand a card from a player
 * and add it too the current fall; it will call removecard to remove the pointer to the Card from
 * the hand of the player
 * @param table - The array contening the adress of each Player of the game.
 * @param falls - An array of pointer on Card contening all the Cards that have been played this round.
 * @param playerid - The id of the player who wish to play.
 * @param cardid - The id of the card he wish to play.
 * @param sizefalls - A pointer on the current size of the falls
 * @param newposition - The Card position in the future game; corespond to the order in which this card is played
 */
Boolean playcard(Player** table,Card** falls,int playerid,int cardid,int* sizefalls,int* newposition);
/**
 * This will deal the cards to each player
 * @param table - The array contening the adress of each Player of the game.
 * @param deck - The array contening the adress of each Card of the game.
 * @param dealerid - The id of the player who's dealing this game.
 */
void cardsdeal(Player** table,Card** deck,int dealerid);
/**
 * This function will parse trought the dack and set the trump value of the selected color to TRUE
 * @param deck - The array contening the adress of each Card of the game.
 * @param trump - The color that will become the trump.
 */
void definetrump(Card** deck,char trump);

/**
 * This function generate and return an array containing all player data.
 * Player 1 (South) is the user,he's teaming with Player 3 (North IA).
 * The other Player 2 (West IA) and  Player 4 (East IA) are together.
 * @return an array of 4 pointers on Player.
 */
Player** createplayer();

/**
 * This function generate and return the set of 32 cards that will be used during the game.
 * In order to avoid copying Cards into players hand, we'll be manipulating pointers.
 * @return an array of 32 pointers on Card, their player value is set to 0 by default.
 */
Card** createcards();


/**
  * This function will be called in End of turn if at least one trump has been played.
  * it will look through the array and return the id of the player who has won the turn.
  * @param fallstrump - An array of pointer on Card contening all the trumps that have been played.
  * @param size - the size of the passed array
  * @param max - The value of the strongest trump, used in checkcard mostly
  * @return a int containing the id of the winning player
*/
int whowintrump(Card** fallstrump,int size,int* max);

/**
  * This function will be called in End of turn if no trump have been played.
  * it will look through the array and return the id of the player who has won the turn.
  * @param falls - An array of pointer on Card contening all the Cards that have been played this round.
  * @param sizefalls - The acctual size of the fall.
  * @param max - The value of the strongest Card, used in IAcompute mostly.
  * @return a int containing the id of the winning player
*/
int whowin(Card** falls,int sizefalls,int* max);

/**
 * This function will be lunched ones everybody has played a card.
 * Its role is to modify the card.player value, setting it to the -1,-2,-3 or -4 depending on which player won.
 * It annytrump to count the trump in the fall
 * whowin and whowintrump are used to determine the id of the winning player.
 * @param falls - The address of the cards that have been played by each player.
 * @return a int containing the id of the winning player or -1 if there's a memory allocation error.
 */
int Endofturn(Card** falls);

/**
 * This function go trough the hand of a given player and remove a pointer from it.
 * It will then realloc the hand with its new size.
 * @param table - An array of pointer on player
 * @prama playerid - The id of the player whose hand we'll resize
 * @param index - the index of the card we wish to remove
 * @return A Boolean - TRUE if there's no memory error FALSE otherwise
 */
Boolean removecardsfromhand(Player** table,int playerid,int index);

/**
 * This function go trough an array of pointer of Card.
 * It will give the index of the lowest card supperior to the 3rd parameter
 * It will ignore Cards that are trump.
 * @param cardarray - An array of pointer on Card.
 * @prama size - the size of the array of card.
 * @param supp - the value the returned card is supposed to be superior to.
 * @return the index of lowest card.
 */
int mincard(Card** cardarray,int size,int supp);

/**
 * This function go trough an array of pointer of Card.
 * It will give the index of the lowest card supperior to the 3rd parameter.
 * the 3rd parameter MUST BE ALREADY CONVERTED IN TRUMP VALUE !
 * It exept to work with trump.
 * @param cardarray - An array of pointer on Card.
 * @prama size - the size of the array of card.
 * @param supp - the value the returned card is supposed to be superior to.
 * @return the index of lowest card.
 */
int mintrump(Card** cardarray,int size,int supp);

/**
 * This function go trough an array of pointer of Card.
 * It will give the index of the lowest card supperior to the 3rd parameter.
 * the 3rd parameter MUST BE ALREADY CONVERTED IN TRUMP VALUE !
 * It exept to work with trump.
 * @param deck - The array of pointer on Card contening all the Card of the game .
 * @prama cutfrom - where to cut the array.
 */
void shuffle(Card** deck,int cutfrom);



#endif

