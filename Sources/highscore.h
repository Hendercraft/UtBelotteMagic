/*
 * highscore.h
 *
 *  Created by William Mann
 */

#ifndef HIGHSCORE_HIGHSCORE_H_
#define HIGHSCORE_HIGHSCORE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Cards.h>
#include <menu.h>
#include <structures.h>


/******************************************************************************/
/**************************FUNCTIONS DEFINITION*******************************/
/****************************************************************************/

/*
 * Gets the name typed by the user, verifies it.
 * @return a string, the name of the user
 */
char* playerCheck();


/*
 * Function that counts the lines in the file
 * @return the number of lines in the file
 */
int lineCount();


/*
 * Function that creates an array of highscores from the highscore file
 * @param size - the size of the array
 * @return the pointer to the  array of scores
 */
 highscore* scoreArray(int size);


/*
 * Function that updates the scores in the file
 * @param size - the size of the array
 */
void scoreUpdate(highscore* scores, int size);


 /*
  * Gets and write the name and the score of the person in the file
  * @param victory - boolean that states if the person has won or lose the game
  */
 void scoreWrite(Boolean victory);


 /*
  * sort the scores from the highest to the lowest
  * @param scores - array of highscores
  * @param size - size of the array
  * @return the pointer to the sorted array of scores
  */
 highscore* scoreSorting(highscore* scores, int size);


 /*
  * Swap the two highscores at the indexes "index1" and "index2" in the array
  * @param scores - a array of highscores
  * @param index1 - an existing index in "myarray" to swap with "index2"
  * @param index2 - an existing index in "myarray" to swap with "index2"
  */
 void swap(highscore* scores, int index1, int index2);


int* teamFoldPoints(Card** deck, Bet contract);

int* scoreCount(Bet contract,Card** deck);


#endif /* HIGHSCORE_HIGHSCORE_H_ */
