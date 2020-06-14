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


    //Menu Printing
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

    //Game beginning

    char* playerName = (char*)malloc(sizeof(char)*15);
	playerName = playerCheck();
    clrscr();

    int numberCardsPlayed=1;
    srand(time(0));



    ////BETTING TIME///
    clrscr();

    Bet previousBet = {0,0,'n',0,-1};
    Card** deck = createcards();
    Player** table = createplayer();
    int dealer, beginning=0;
    dealer = beginning;

    do{
        beginning = 2;// rand()%3+1; //generates a random number in [1,4] to know who begins
        dealer = beginning;
        int sameBet=0, betTurn=0;
        Bet nextBet;

        cardsdeal(table,deck,dealer);

        previousBet.coinche = 0;
        previousBet.contract = 0;
        previousBet.points = 0;
        previousBet.team = -1;
        previousBet.trump = 'n';

        //shuffle and dealing cards
        //shuffle(deck,-1);
        cardsdeal(table,deck,dealer);


        do{ //repeats until a bet is made

            if (beginning>3){
                beginning=0;
            }

            nextBet = botBet(table,previousBet,beginning);
            if(previousBet.coinche == nextBet.coinche && previousBet.contract == nextBet.contract && previousBet.points == nextBet.points && previousBet.team == nextBet.team && previousBet.trump == nextBet.trump){
                    switch(beginning){
                    case 1:
                        printf("West Passed\n");
                        break;
                    case 2:
                        printf("North Passed\n");
                        break;
                    case 3:
                        printf("East Passed\n\n");
                        break;

                    }
                    sameBet ++;
            } else {
                sameBet = 0;
            }

            previousBet.coinche = nextBet.coinche;
            previousBet.contract = nextBet.contract;
            previousBet.points = nextBet.points;
            previousBet.team = nextBet.team;
            previousBet.trump = nextBet.trump;
            beginning ++;
            betTurn ++;

        }while((sameBet < 3 || betTurn<4) && (sameBet < 3 || betTurn<4 || (previousBet.coinche == 0 || previousBet.contract == 0 || previousBet.points == 0 || previousBet.team == -1 || previousBet.trump == 'n')));
    }while(previousBet.coinche == 0 && previousBet.contract == 0 && previousBet.points == 0 && previousBet.team == 0 && previousBet.trump == 'n');


    ///PLAYING TIME///

    definetrump(deck,previousBet.trump);//setting the trump in the deck
    int winner; //id of the player winning the fold


    for(int j=0;j<8;j++){ // repeats until all cards in hand are played

        winner = turn(table, previousBet, playerName, previousBet.team+1, &numberCardsPlayed);//playing a turn
        printf("%d",winner);
    }


	return EXIT_SUCCESS;



}
