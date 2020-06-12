/*
 * main.c
 *
 *  Created by William Mann
 */

#include <highscore.h>
#include <menu.h>
#include <Cards.h>
#include <bet.h>
#include <time.h>


int main(){


	int operation, play=0;

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

    /*scoreWrite(true);

    return EXIT_SUCCESS;*/

    clrscr();

    srand(time(0));
	int dealer = 1, beginning;
	bet previousBet = {0,0,'n'};
	Card** deck = createcards();
	Player** table = createplayer();

	cardsdeal(table,deck,dealer);

    beginning = rand()%3; //generates a random number in [0,3] to know who begins

    if(beginning == 0){
        previousBet = betMenu(table, previousBet);
        previousBet = botBet(table, previousBet, 1);
        previousBet = botBet(table, previousBet, 2);
        previousBet = botBet(table, previousBet, 3);
    } else if(beginning == 1){
        previousBet = botBet(table, previousBet, 1);
        previousBet = botBet(table, previousBet, 2);
        previousBet = botBet(table, previousBet, 3);
        previousBet = betMenu(table, previousBet);
    } else if(beginning == 2){
        previousBet = botBet(table, previousBet, 2);
        previousBet = botBet(table, previousBet, 3);
        previousBet = betMenu(table, previousBet);
        previousBet = botBet(table, previousBet, 1);
    } else {
        previousBet = botBet(table, previousBet, 3);
        previousBet = betMenu(table, previousBet);
        previousBet = botBet(table, previousBet, 1);
        previousBet = botBet(table, previousBet, 2);
    }

	printf("%d %d %c",previousBet.contract,previousBet.points,previousBet.trump);

	return EXIT_SUCCESS;
}
