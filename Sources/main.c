/*
 * main.c
 *
 *  Created by William Mann
 */

#include <highscore.h>
#include <menu.h>
#include <Cards.h>
//#include <bet.h>


int main(){


	/*int operation, play=0;

		FILE* file= fopen("highscore.txt","a");
		fclose(file);

		while(play==0){

			clrscr();
			menuVisual();

				operation = verify(3);
				if(operation == 1){
					clrscr();
					printf("Launching game...");
					play=1;

				} else if(operation == 2){
					clrscr();
					scoreVisual();
					operation = verify(2);
					if(operation==2){
						return EXIT_SUCCESS;
					}

				} else if(operation == 3){
					clrscr();
					printf("See you next time !");
					return EXIT_SUCCESS;
				}


		}

		return EXIT_SUCCESS;*/

		/*scoreWrite(true);

		return EXIT_SUCCESS;*/


	/*Cards* deck = createCards();
	char* playerHand;

	Cards* player = hand(deck,32);

	playerHand = handString(player);

	printf("%s",playerHand);*/

	int dealer = 1;
	Card** deck = createcards();
	for (int i=0; i<4; i++){  // Color's loop, each new loop mean a new color, first will be heart than club, diamond and spade
				for (int value=0; value<8;value++){ //Value's loop, each new loop mean a new card

					printf("%d",deck[value+8*i]->value);
					printf("%c",deck[value+8*i]->color);
					printf("%d",deck[value+8*i]->player);
					printf("%d",deck[value+8*i]->trump);
					printf("%d\n",deck[value+8*i]->position);
				}
			}
	Player** table = createplayer();
	for (int i=0; i<4; i++){
				printf("%d",table[i]->id);
				printf("%d",table[i]->bet);
				printf("%d\n",table[i]->hand_size);
			}
	cardsdeal(table,deck,dealer);
	for (int i=0; i<4; i++){
		printf("%d",table[i]->id);
		printf("%d",table[i]->bet);
		printf("%d\n",table[i]->hand_size);
		for (int j=0; j<8; j++){
			printf("Player %d , Card[%d]=%d\n",i,j,table[i]->Hand[j]->player);
		}
	}


	/*betMenu(table);*/


	return EXIT_SUCCESS;
}
