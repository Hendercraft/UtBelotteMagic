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

    char* playerName = (char*)malloc(sizeof(char)*15);
	playerName = playerCheck();
    clrscr();

    int numberCardsPlayed=1;
    srand(time(0));

    for(int j=0;j<8;j++){ // tried a boucle

        ////BETTING TIME///
        clrscr();

        Bet previousBet = {0,0,'n',0,0};
        Card** deck = createcards();
        Player** table = createplayer();
        int dealer, beginning;
        dealer = beginning;

        do{
            beginning = rand()%3+1; //generates a random number in [1,4] to know who begins
            dealer = beginning;
            int sameBet=0, betTurn=0;
            Bet nextBet;

            cardsdeal(table,deck,dealer);

            previousBet.coinche = 0;
            previousBet.contract = 0;
            previousBet.points = 0;
            previousBet.team = 0;
            previousBet.trump = 'n';


            do{

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

            }while((sameBet < 3 || betTurn<4) && (sameBet < 3 || betTurn<4 || (previousBet.coinche == 0 || previousBet.contract == 0 || previousBet.points == 0 || previousBet.team == 0 || previousBet.trump == 'n')));
        }while(previousBet.coinche == 0 && previousBet.contract == 0 && previousBet.points == 0 && previousBet.team == 0 && previousBet.trump == 'n');

        return EXIT_SUCCESS;

        ///PLAYING TIME///

        //shuffle and dealing cards
        shuffle(deck,-1);
        cardsdeal(table,deck,dealer);

        //initializing a falls
        Card** falls = (Card**)malloc(sizeof(Card*));
        falls[0] = NULL;
        int playedCard,size=0,numberOfPlayables = 0,chosenCard;
        int *playableCards/*the cards you can play*/;
        Boolean cardPlayed=FALSE;


        for(int i=beginning; i<beginning+4; i++){
            clrscr();
            ingameMenu(previousBet,playerName,table, falls,i%4+1);
            if(i%4 == 0){
                do{
                    playableCards = checkcard(table,falls,1,size,&numberOfPlayables);
                    chosenCard = verify(0,table[0]->hand_size);

                    for(int j=0;j<numberOfPlayables;j++){
                        if(chosenCard-1 == playableCards[j]){
                            cardPlayed = playcard(table,falls,1,playedCard,&size,&numberCardsPlayed);
                        }
                    }
                }while(cardPlayed == FALSE);

            } else {
                //fait en sorte que l'ia puisse jouer une carte ici
                playableCards = checkcard(table,falls,i%4+1,size,&numberOfPlayables);
                playedCard = IAcompute(table,falls,i%4+1,size,playableCards,numberOfPlayables);
                cardPlayed = playcard(table,falls,i%4+1,playedCard,&size,&numberCardsPlayed);
            }
            cardPlayed = FALSE;
            //aggrandir falls
        }
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
