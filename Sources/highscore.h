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


/* Creation of structure composed of: */
typedef struct {
	int victories; /*an integer for the number of victories*/
	int loses; /*an integer for the number of loses*/
	char name[15]; /*a string for the name of the player*/
} highscore;

typedef enum {
	false = 0,
	true = 1
} boolean;

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
 * Function that creates an array of highscores
 * @return the pointer to the  array of scores
 */
 highscore* scoreArray(int size);


/*
 * Function that updates the score of a player
 */
void scoreUpdate(highscore* scores, int size);


 /*
  * Gets and write the name and the score of the person in the file
  * @param
  */
 void scoreWrite(boolean victory);


 /*
  * sort the scores from the highest to the lowest
  * @param scores - array of highscores
  * @param size - sie of the array
  */
 highscore* scoreSorting(highscore* scores, int size);


 /**
  * Swap the two highscores at the indexes "index1" and "index2" in the array
  * @param scores - a array of highscores
  * @param index1 - an existing index in "myarray" to swap with "index2"
  * @param index2 - an existing index in "myarray" to swap with "index2"
  */
 void swap(highscore* scores, int index1, int index2);


#endif /* HIGHSCORE_HIGHSCORE_H_ */
