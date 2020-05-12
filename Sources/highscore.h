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
} Highscore;


/*
 * Checks if the highscore.txt file is present, if not it creates it
 */
void fileCheck();

/*
 * Gets and write the name and the score of the person in the file
 */
void scoreWrite(int score);

/*
 * Does a thing but idk yet
 */
void thing();

#endif /* HIGHSCORE_HIGHSCORE_H_ */
