/*
 * main.c
 *
 *  Created by William Mann
 */

#include <highscore.h>
#include <menu.h>
#include <Cards.h>
#include <bet.h>
#include <structures.h>


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

    /*srand(time(0));
	int dealer = 1, beginning;/*sameBet;*/
	Bet previousBet = {0,0,'n',0};/*nextBet;*/
	Card** deck = createcards();
	Player** table = createplayer();

	cardsdeal(table,deck,dealer);

    beginning = rand()%3 + 1; //generates a random number in [0,3] to know who begins
	//RANT A 2 H DU MAT, GUILLAUME FIX CA
    /*do{
        
    }while(sameBet != 3 || (sameBet != 3 %%)) */
    
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

	///PLAYING TIME///
    clrscr();
	char* playername = (char*)malloc(sizeof(char)*15);
	playername = playerCheck();
    clrscr();

	//shuffle and dealing cards
	shuffle(deck,-1);
	cardsdeal(table,deck,dealer);
	int whoplay[7] = {0,1,2,3,0,1,2}; // cheap trick that avoid me writing some if
	for (int round =1; roud<9 ; round++){
		
		Card** falls = malloc (sizeof(Card*));
		int sizeofplayable = 0;
		checkcard(table,falls,dealer,0,&sizeofplayable);
		
		
	/*initializing a test falls
	Card** falls = (Card**)malloc(sizeof(Card*));
    falls[0] = (Card*) malloc(sizeof(Card));*/
	 
	
	

	return EXIT_SUCCESS;




	/*int dealer = 1;
	Card** deck = createcards();
	Player** table = createplayer();

	int* playableCards;

	cardsdeal(table,deck,dealer);

    Card** falls = (Card**)malloc(sizeof(Card*)*4);
    for(int i=0;i<4;i++){

        falls[i] = (Card*) malloc(sizeof(Card));
    }

    definetrump(deck,'c');

    playableCards = checkcard(table, falls, 1, 4);
    if (playableCards == NULL){
        printf("Error dumbass");
    }else{
        for(int i=0; i<8;i++){
            printf("%d\n",playableCards[i]);
        }
    }

	return EXIT_SUCCESS;*/


    /*int dealer = 1;
    int* teamPoints;
    Card** deck = createcards();
	Player** table = createplayer();
    cardsdeal(table,deck,dealer);

    Bet previousBet = {1,80,'t',0,1};

    teamPoints = scoreCount(previousBet,deck);
    printf("%d %d",teamPoints[0],teamPoints[1]);

	return EXIT_SUCCESS;*/

	/*srand(time(0));
	Card** deck = createcards();
	shuffle(deck,-1);

    for(int i=0; i<32;i++){
        printf("%d ",deck[i]->position);
    }
    return EXIT_SUCCESS;*/
}
