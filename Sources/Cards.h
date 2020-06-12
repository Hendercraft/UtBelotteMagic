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
    int player; // The owner of the card, 0 means unowned , 1 to 4 is the played id
    //It can be also set to -1 or -2, if the card has been played and won either by one team or the other
    Boolean trump; //Is the card a trump ?
    int position; // Its position in the deck
} Card;
/* Player type definition */
typedef struct{
	Card** Hand;
	int id;
	int bet;
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
 * @return an array of int - This array will containt the index of each playedable card.
 */
int* checkcard(Player** table,Card** falls ,int playerid,int sizefalls);



/**
 * This function will take a card that has already been tested from the hand a card from a player
 * and add it too the current fall; it will call removecard to remove the pointer to the Card from
 * the hand of the player
 * @param table - The array contening the adress of each Player of the game.
 * @param falls - An array of pointer on Card contening all the Cards that have been played this round.
 */
void playcard(Player** table,Card** falls);
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
 * Its role is to modify the card.player value, setting it to -1 or -2 depending of the team who has won.
 * It rely on whowin and whowintrump to do so.
 * @param falls - The address of the cards that have been played by each player.
 * @return a int containing the id of the winning player
 */
int Endofturn(Card** falls);


#endif

