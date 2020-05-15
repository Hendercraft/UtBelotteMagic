/*
 * InGame.c
 *
 *  Created by William Mann
 */


#include <ingame.h>


/*
 * Prints the cards in the player's hand
 */
void handPrint(Cards* Cards, int size){

}


/*
 * Function that prints a card
 */
void cardPrint(char number, char color){

	if (color == 'H'){
		printf(".---------.\n|%c.-----. |\n| : _ _ : |\n| :( V ): |\n| : \\ / : |\n| :  V  : |\n| '-----'%c|\n`---------'",number,number);
	} else if (color == 'C'){
		printf(".---------.\n|%c.-----. |\n| :  _  : |\n| : (_) : |\n| :( | ): |\n| : '^' : |\n| '-----'%c|\n`---------'",number,number);
	} else if (color == 'S'){
		printf(".---------.\n|%c.-----. |\n| :  ^  : |\n| : /_\\ : |\n| :(___): |\n| :  |  : |\n| '-----'%c|\n`---------'",number,number);
	}else if (color == 'D'){
		printf(".---------.\n|%c.-----. |\n| :  ^  : |\n| : / \\ : |\n| : \\ / : |\n| :  V  : |\n| '-----'%c|\n`---------'",number,number);
	}
}


