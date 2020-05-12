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


/* Creation of an Highscore type who takes 15 letters for the name of the user and then numbers for the score */
typedef struct {
	int score;
	char name[15];
} highscore;


/*
 * Checks if the highscore.txt file is present, if not it creates it
 */
void fileCheck();

/*
 * Gets and write the name and the score of the person in the file
 */
void scoreWrite(int score);

/*
 * Function that counts the lines in the file
 * @return the number of lines in the file
 */
int lineCount();

/*
 * Function that creates an array of highscores
 * @return the pointer to the  array of scores
 */
 highscore* scoreArray();

/*
 * Does a thing but idk yet
 */
void thing();

#endif /* HIGHSCORE_HIGHSCORE_H_ */
