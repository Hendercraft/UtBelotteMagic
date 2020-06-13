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

    ////BETTING TIME///
    clrscr();

    srand(time(0));
	int dealer = 1, beginning;
	Bet previousBet = {0,0,'n',0};
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

	///PLAYING TIME///
    clrscr();
	char* player = (char*)malloc(sizeof(char)*15);
	player = playerCheck();
    clrscr();
	//dealing cards
	cardsdeal(table,deck,dealer);

	//initializing a test falls
	Card** falls = (Card**)malloc(sizeof(Card*)*4);
    for(int i=0;i<3;i++){
        falls[i] = (Card*) malloc(sizeof(Card));
    }

    falls[0]->color = 's';
    falls[0]->player = 3;
    falls[0]->position = 1;
    falls[0]->trump = FALSE;
    falls[0]->value = 0;

    falls[1]->color = 's';
    falls[1]->player = 4;
    falls[1]->position = 2;
    falls[1]->trump = FALSE;
    falls[1]->value = 3;



	ingameMenu(previousBet,player,table, falls,2);

	return EXIT_SUCCESS;

	/*int dealer = 1;
	Card** deck = createcards();
	Player** table = createplayer();

	int* playableCards;

	cardsdeal(table,deck,dealer);

    Card** falls = (Card**)malloc(sizeof(Card*)*4);
    for(int i=0;i<3;i++){
        falls[i] = (Card*) malloc(sizeof(Card));
    }
    falls[0]->color = 's';
    falls[0]->player = 3;
    falls[0]->position = 1;
    falls[0]->trump = FALSE;
    falls[0]->value = 0;

    falls[1]->color = 'd';
    falls[1]->player = 4;
    falls[1]->position = 2;
    falls[1]->trump = TRUE;
    falls[1]->value = 0;

    definetrump(deck,'d');

    playableCards = checkcard(table, falls, 1, 2);

    for(int i=0; i<8;i++){
        printf("%d\n",playableCards[i]);
    }

	return EXIT_SUCCESS;*/
}
