/*
 * menu.h
 *
 *  Created by William Mann
 */

#ifndef MAINMENU_MENU_H_
#define MAINMENU_MENU_H_


/*Libraries used*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Cards.h>

/*This series of protocol just set the output color on Unix-like systems */

void magenta (int bold);
void reset();
void green(int bold);
void yellow(int bold);
void blue(int bold);
void red(int bold);
void cyan (int bold);

/******************************************************************************/
/****************************DISPLAY FUNCNCTIONS******************************/
/****************************************************************************/




/*
 * This fonction will display a single card in ASCII art
 * If the output system is Unix-like the output will be colored
 */
void printcard(Card card)
 	
 
/*
 * Function thats prints the Programm's menu in ASCII art.
 */
void menuVisual();

/*
 * Function thats prints the Highscore's menu in ASCII art.
 */
void scoreVisual();

/*
 * Function that verifies if the is a number between 0 and n
 * @parameter n - integer max
 * @return a number
 */
int verify(int n);

/*
 * Function to clear the cmd
 */
void clrscr();

#endif /* MAINMENU_MENU_H_ */
