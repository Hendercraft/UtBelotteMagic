/*
 * InGame.c
 *
 *  Created by William Mann
 */


#include <ingame.h>


Cards* createCards(){
    Cards* deck = (Cards*) malloc(32 * sizeof(Cards));
    char* color = "hcds"; /* It'll itertate over it to define the color*/
    if (deck != NULL){
        for (int i=0; i<4; i++){
            for (int value=0; value<8;value++){

            	if(value < 2){
            		deck[value+8*i].value = value+1 + '0';
            	} else if (value == 4) {
            		deck[value+8*i].value = 'X';
            	} else if (value == 5) {
            		deck[value+8*i].value = 'J';
            	} else if (value == 6) {
            		deck[value+8*i].value = 'Q';
            	} else if (value == 7) {
            	    deck[value+8*i].value = 'K';
            	} else {
            		deck[value+8*i].value = value+6 + '0';
            	}

                deck[value+8*i].color = color[i];

                if (value == 2 || value == 4){
                	deck[value+8*i].player=-1;
                } else {
                	deck[value+8*i].player = 0;
                }

                deck[value+8*i].trump = false;

        		printf("%c,%c,%d\n",deck[value+i*8].value,deck[value+i*8].color,deck[value+i*8].player);


            }
        }
    } else {
        fprintf( stderr, "there is an error with the memory allocation for the array of Cards");
    }

    return deck;

}


/*
 * Prints the cards in the player's hand
 */
void handPrint(Cards* cards, int size){

	Cards* player = (Cards*) malloc(8*sizeof(Cards));
	int j=0, i=0;

	while(i<size && j<8){

		if(cards[i].player == -1){
			player[j] = cards[i];
			j++;
		}

		i++;
	}

	for(int k=0;k<8;k++){
		printf("%c,%c,%d\n",player[k].value,player[k].color,player[k].player);
	}
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

