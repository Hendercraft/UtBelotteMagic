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

    srand(time(0));
	int beginning = rand()%3+1; //generates a random number in [0,3] to know who begins
	int sameBet,dealer = beginning;
	Bet previousBet = {0,0,'n',0,0},nextBet;
	Card** deck = createcards();
	Player** table = createplayer();

	cardsdeal(table,deck,dealer);



    do{

        if (beginning>3){
            beginning=0;
        }

        nextBet = botBet(table,previousBet,beginning);
        if(previousBet.coinche == nextBet.coinche && previousBet.contract == nextBet.contract && previousBet.points == nextBet.points && previousBet.team == nextBet.team && previousBet.trump == nextBet.trump){
                sameBet ++;
        }

        previousBet.coinche = nextBet.coinche;
        previousBet.contract = nextBet.contract;
        previousBet.points = nextBet.points;
        previousBet.team = nextBet.team;
        previousBet.trump = nextBet.trump;
        beginning ++;

    }while(sameBet != 4 || (sameBet != 3 && (previousBet.coinche == 0 && previousBet.contract == 0 && previousBet.points == 0 && previousBet.team == 0 && previousBet.trump == 'n')));


	///PLAYING TIME///
    clrscr();
	char* playerName = (char*)malloc(sizeof(char)*15);
	playerName = playerCheck();
    clrscr();

	//shuffle and dealing cards
	shuffle(deck,-1);
	cardsdeal(table,deck,dealer);

	//initializing a falls
	Card** falls = (Card**)malloc(sizeof(Card*));
    falls[0] = NULL;

    for(int i=beginning; i<beginning+4; i++){

        ingameMenu(previousBet,playerName,table, falls,1);
    }


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
