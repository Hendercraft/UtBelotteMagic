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
	char name[15];
	int score;
} Highscore;


/*
 * Checks if the highscore.txt file is present, if not it creates it
 */
void fileCheck();

/*
 * Gets and write the name and the score of the person in the file
 */
void scoreWrite();

/*
 * Sort the file from the best to the worst score, and erase the worst one if there is 2 same names
 */
void scoreSort();


#endif /* HIGHSCORE_HIGHSCORE_H_ */
