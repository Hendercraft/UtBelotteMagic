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
/**************************FUNCTIONS DEFINITION*****************************/
/****************************************************************************/

/**
 * This will deal the cards to each player
 * @param table - The array contening all the player data.
 * @param deck - The deck contening all the cards.
 * @param dealerid - The id of the player who's dealing this game. 
 */
void cardsdeal(Player** table,Card** deck,int dealerid);

/**
 * This function generate and return an array containing 4 players.
 * Player 1 (South) is the user,he's teaming with Player 3 (North IA).
 * The other Player 2 (West IA) and  Player 4 (East IA) are together.
 * @return an array of 4 players. 
 */
Player* createplayer();

/**
 * This function generate and return the set of 32 cards that will be used during the game.
 * @return an array of 32 cards, their player value is set to 0 by default. 
 */
Card* createcards();


/**
  * This function will be called in Ebdofturn if at least one trump has been played.
  * it will look trought the array and return the id of the player who have won the turn.
  * @param fallstrump - The trump that have been played by each player
  * @param size - the size of the passed array
  * @return a int contening the id of the winning player
*/
int whowintrump(Card* fallstrump,int size);

/**
  * This function will be called in Ebdofturn if no trump have been played.
  * it will look trought the array and return the id of the player who have won the turn.
  * @param falls - The cards that have been played by each player
  * @return a int contening the id of the winning player
*/
int whowin(Card* falls);

/**
 * This function will be lunched ones everybody has played a card.
 * Its role is to modify the card.player value, setting it to -1 or -2 depending of the team who has won.
 * It relly on whowin and whowintrump to do so.
 * @param falls - The adress of the cards that have been played by each player.
 * @return a int contening the id of the winning player
 */
int Endofturn(Card** falls);


#endif

