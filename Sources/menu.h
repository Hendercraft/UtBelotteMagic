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
#include <display.h>


/*
 * Function thats prints the Programm's menu in ASCII art.
 */
void menuVisual();

/*
 * Function that verifies if the is a number between 0 and n
 * @parameter n - integer max
 * @return a number
 */
int verify(int n);


#endif /* MAINMENU_MENU_H_ */
