#ifndef CARDS_H
#define CARDS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


/******************************************************************************/
/****************************STRUCTURE DEFINITION*****************************/
/****************************************************************************/


/* Boolean type definition */
typedef enum {
 FALSE = 0,
 TRUE = 1
} Boolean;
/* Card type definition */
typedef struct {
    int value; //Card value,between 0 and 7
    char color; // Either c for clubs h for heart .......
    int player; // The owner of the card, 0 means unowned ,1 to 4 is the played id.
    //It can be also set to -1-,2,-3,4 if the card has been played and won either by player 1,2......
    Boolean trump; //Is the card a trump ?
    int position; // Its position in the deck
} Card;
/* Player type definition */
typedef struct{
	Card** Hand;
	int id;
	int hand_size;
} Player;

/******************************************************************************/
/**************************FUNCTIONS DEFINITION*******************************/
/****************************************************************************/


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
 * @return an array of int - This array will containt the index of each playedable card, retrun NULL if there's an error with malloc.
 */
int* checkcard(Player** table,Card** falls ,int playerid,int sizefalls);



/**
 * This function will take a card that has already been tested from the hand of a player.
 * It will realloc the current fall to add en empty place at its end.
 * It wil then copy the pointer on card from the hand of the player to the fall.
 * @param table - The array contening the adress of each Player of the game.
 * @param playerid - The id of play who's playing a card.
 * @param cardid - The ID of the card he's playing.
 * @param sizefalls - The current size of the fall
 * @param falls - An array of pointer on Card contening all the Cards that have been played this round.
 * @return a Boolean, TRUE if there's no problem, FALSE otherwise
 */
Boolean playcard(Player** table,Card** falls,int playerid,int cardid,int* sizefalls);
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
  * @param max - The value of the strongest trump, used in cehckcard mostly
  * @return a int containing the id of the winning player
*/
int whowintrump(Card** fallstrump,int size,int* max);

/**
  * This function will be called in End of turn if no trump have been played.
  * it will look through the array and return the id of the player who has won the turn.
  * @param falls - An array of pointer on Card contening all the Cards that have been played this round.
  * @param sizefalls - The acctual size of the fall
  * @return a int containing the id of the winning player
*/
int whowin(Card** falls,int sizefalls);

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

#endif

