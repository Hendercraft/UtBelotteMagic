/*
 * display.h
 *
 *  Created by William Mann
 */

#ifndef MAINMENU_DISPLAY_H_
#define MAINMENU_DISPLAY_H_


/*Libraries used*/
#include <stdio.h>
#include <stdlib.h>


/*This series of protocol just set the output color */

void magenta (int bold);
void reset();
void green(int bold);
void yellow(int bold);
void blue(int bold);
void red(int bold);
void cyan (int bold);

#endif /* MAINMENU_DISPLAY_H_ */
