/*
 * main.c
 *
 *  Created by William Mann
 */

#include <highscore.h>
#include <menu.h>

int main(){

	int operation;

	menuVisual();

	operation = verify(3);
	if(operation == 1){
		clrscr();
		printf("Launching game...");
		return EXIT_SUCCESS;

	} else if(operation == 2){
		clrscr();
		printf("Showing highscores...");
		return EXIT_SUCCESS;

	} else if(operation == 3){
		return EXIT_SUCCESS;
	}

}

