/*
 * bet.c
 *
 *  Created by William Mann
 */

#include <bet.h>

/*
 * Displays the bet menu for the player
 */
Bet betMenu(Player** table, Bet previousChoice){

    //creates the strings for the trump and symbols
    #if defined(_WIN32) || defined(__MSDOS__)
        #define SPADE   "\x06"
        #define CLUB    "\x05"
        #define HEART   "\x03"
        #define DIAMOND "\x04"
        #define ALLTRUMP "All Trump"
        #define NOTRUMP "No Trump"
    #else
        #define SPADE   "\xE2\x99\xA0"
        #define CLUB    "\xE2\x99\xA3"
        #define HEART   "\xE2\x99\xA5"
        #define DIAMOND "\xE2\x99\xA6"
        #define ALLTRUMP "All Trump"
        #define NOTRUMP "No Trump"
    #endif

    char valueArray[8]={'7','8','9','J','Q','K','X','A'};

	char titleAsciiArt[]="\n########  ######## ########  ######\n##     ## ##          ##    ##    ##\n##     ## ##          ##    ##\n########  ######      ##     ######\n##     ## ##          ##          ##\n##     ## ##          ##    ##    ##\n########  ########    ##     ######\n";
	char lineAsciiArt[]="\n**---------------------------------------------------------------------------**\n\n";
	char pointsAsciiArt[]="1) N points - Your teams gets a minimum of N points:\nN points\n\n";
	char capotAsciiArt[]="2) Capot - Your teams must win all folds:\n250 points\n\n";
	char generaleAsciiArt[]="3) Generale - You must win all folds:\n500 points\n\n";
	char coincheAsciiArt[]="4) Coinche - The before stated contract cannot be full filled:\nprevious contract x 2 points\n\n";
	char surcoincheAsciiArt[]="5) Surcoinche - The coinched contract can be full filled:\nprevious coinche x 2 points\n\n";
	char pass[]="6) Pass\n";

	int choice,number=0,trump;
	Bet playerBet;

	magenta(1);
	printf("%s",titleAsciiArt);

	reset();
	printf("%s%s%s%s%s%s%s%s",lineAsciiArt,pointsAsciiArt,capotAsciiArt,generaleAsciiArt,coincheAsciiArt,surcoincheAsciiArt,pass,lineAsciiArt);

    printf("Your Hand is:\n");
	for(int i=0;i<(table[0]->hand_size);i++){
        printf("%c",valueArray[table[0]->Hand[i]->value]);
        if(table[0]->Hand[i]->color == 'h'){
            printf("%s ",HEART);
        } else if(table[0]->Hand[i]->color == 's'){
            printf("%s ",SPADE);
        } else if(table[0]->Hand[i]->color == 'd'){
            printf("%s ",DIAMOND);
        } else {
            printf("%s ",CLUB);
        }
	}
    printf("\n");

	do{
		if (previousChoice.contract == 0){
			do {
				printf("There is no previous contract, so you can't coinche or surcoinche.\n");
				choice = verify(0,6);
			} while (choice == 5 || choice == 4);
		}
		else {
            printf("The previous contract has a value of %d and a trump of %c,\n",previousChoice.points,previousChoice.trump);
            if (previousChoice.coinche==0){
                do {
                    printf("You can't surcoinche.\n");
                    choice = verify(0,6);
                } while (choice == 5);
            } else {
                do {
                    printf("There is a coinche so you can't coinche again.\n");
                    choice = verify(0,6);
                } while (choice == 4);
            }
		}

		switch(choice) {

		case 1:
			do{
				printf("What is the value between 80 and 160 for n ?\n");
				number = verify(80,160);
			}while(number>160 || number<80);
            playerBet.contract = choice;
			break;

		case 2:
			number = 250;
			playerBet.contract = choice;
			break;

		case 3:
			number = 500;
			playerBet.contract = choice;
			break;

		case 4:
		    number = previousChoice.points*2;
			playerBet.contract = previousChoice.contract;
			playerBet.coinche = 1;
			break;
		case 5:
			number = previousChoice.points*2;
			playerBet.contract = previousChoice.contract;
			playerBet.coinche = 2;
			break;

        case 6:
            return previousChoice;

		}

		printf("\nWhich Trump do you want ?\n");
		printf("1) %s \n",SPADE);
		printf("2) %s \n",HEART);
		printf("3) %s \n",CLUB);
		printf("4) %s \n",DIAMOND);
		printf("5) %s \n",ALLTRUMP);
		printf("6) %s \n",NOTRUMP);

		trump = verify(1,6);

		switch(trump){

        case 1:
            playerBet.trump = 's';
            break;

        case 2:
            playerBet.trump = 'h';
            break;

        case 3:
            playerBet.trump = 'c';
            break;

        case 4:
            playerBet.trump = 'd';
            break;

        case 5:
            playerBet.trump = 't';
            break;

        case 6:
            playerBet.trump = 'n';
            break;
		}

		if(previousChoice.points>number && choice != 6){
			printf("You need to make an higher contract than the previous one or pass.\n\n");
		}
	} while(previousChoice.points>number && choice != 6);

	playerBet.points = number;
	playerBet.team = 1;

	return playerBet;

}


Bet botBet(Player** table, Bet previousChoice, int botNb){

    int nbH=0,nbS=0,nbC=0,nbD=0,max=0;
    int *hCards = (int*)malloc(sizeof(int)*8);
    int *sCards = (int*)malloc(sizeof(int)*8);;
    int *cCards = (int*)malloc(sizeof(int)*8);;
    int *dCards = (int*)malloc(sizeof(int)*8);;

    for(int i=0;i<table[botNb]->hand_size;i++){

        if(table[botNb]->Hand[i]->color == 'h'){
            hCards[nbH-1] = table[botNb]->Hand[i]->value;
            nbH ++;
        } else if(table[botNb]->Hand[i]->color == 'd'){
            dCards[nbD-1] = table[botNb]->Hand[i]->value;
            nbD ++;
        } else if(table[botNb]->Hand[i]->color == 'c'){
            cCards[nbC-1] = table[botNb]->Hand[i]->value;
            nbC ++;
        } else {
            sCards[nbS-1] = table[botNb]->Hand[i]->value;
            nbS ++;
        }
    }

    nbH = howManyStrong(hCards, nbH, TRUE);
    nbS = howManyStrong(sCards, nbS, TRUE);
    nbD = howManyStrong(dCards, nbD, TRUE);
    nbC = howManyStrong(cCards, nbC, TRUE);

    max = (nbH > nbS ? nbH : nbS) > (nbD > nbC ? nbD : nbC) ? (nbH > nbS ? nbH : nbS) : (nbD > nbC ? nbD : nbC); // Find the maximum between the number of strong cards in every color

    /*free(hCards);
    free(dCards);
    free(cCards);
    free(sCards);*/

    if(max >= 3){
        if(max == 3 && previousChoice.points<80){
            previousChoice.contract = 1;
            previousChoice.points = 80;
        } else if(max > 3 && previousChoice.points<120){
            previousChoice.contract = 1;
            previousChoice.points = 120;
        }

        if (max == nbH){
            previousChoice.trump = 'h';
        } else if (max == nbS){
            previousChoice.trump = 's';
        } else if (max == nbD){
            previousChoice.trump = 'd';
        } else {
            previousChoice.trump = 'c';
        }

        if(botNb == 2){
            previousChoice.team = 1;
        } else{
            previousChoice.team = 2;
        }

        return previousChoice;
    } else {
        return previousChoice;
    }
}

int howManyStrong(int* cardColorValues, int size, Boolean trump){

    int strongCards=0;

    if(trump == FALSE){
        for(int i=0; i<size;i++){
            if(cardColorValues[i]>3){
                strongCards ++;
            }
        }
    } else {
        for(int i=0; i<size;i++){
            if(cardColorValues[i]>5 || (4>cardColorValues[i] && cardColorValues[i]>1)){
                strongCards ++;
            }
        }
    }

    return strongCards;

}
