/*
 * main.c
 *
 *  Created by William Mann
 */

#include <highscore.h>
#include <menu.h>
#include <Cards.h>
#include <bet.h>


int main(){


	/*int operation, play=0;

		FILE* file= fopen("highscore.txt","a");
		fclose(file);

		while(play==0){

			clrscr();
			menuVisual();

				operation = verify(0,3);
				if(operation == 1){
					clrscr();
					printf("Launching game...");
					play=1;

				} else if(operation == 2){
					clrscr();
					scoreVisual();
					operation = verify(0,2);
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
	bet previousBet = {0,0,'n'};
	Card** deck = createcards();
	Player** table = createplayer();

	cardsdeal(table,deck,dealer);

	previousBet = betMenu(table, previousBet);

	previousBet = botBet(table, previousBet, 3);

	printf("%d %d %c",previousBet.contract,previousBet.points,previousBet.trump);

	return EXIT_SUCCESS;
}
