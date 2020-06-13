/*
 * bet.c
 *
 *  Created by William Mann
 */

#include <bet.h>

/*
 * Displays the bet menu for the player
 * @param table - dynamic array of players with their hand, hand size, etc.
 * @param previousChoice - bet type the previous bet with the contract, the team who made it, the value and if it is coinched or surcoinched
 * @return the new bat made by the player
 */
Bet betMenu(Player** table, Bet previousChoice){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/


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

    char valueArray[8]={'7','8','9','J','Q','K','X','A'}; //Array to transform the value of the card in a char

    // all the art and text for the menu
	char titleAsciiArt[]="\n########  ######## ########  ######\n##     ## ##          ##    ##    ##\n##     ## ##          ##    ##\n########  ######      ##     ######\n##     ## ##          ##          ##\n##     ## ##          ##    ##    ##\n########  ########    ##     ######\n";
	char lineAsciiArt[]="\n**---------------------------------------------------------------------------**\n\n";
	char pointsAsciiArt[]="1) N points - Your teams gets a minimum of N points:\nN points\n\n";
	char capotAsciiArt[]="2) Capot - Your teams must win all folds:\n250 points\n\n";
	char generaleAsciiArt[]="3) Generale - You must win all folds:\n500 points\n\n";
	char coincheAsciiArt[]="4) Coinche - The before stated contract cannot be full filled:\nprevious contract x 2 points\n\n";
	char surcoincheAsciiArt[]="5) Surcoinche - The coinched contract can be full filled:\nprevious coinche x 2 points\n\n";
	char pass[]="6) Pass\n";

	int choice,number=0,trump; //integer for the choice pf the contract, number is the points given by the contract and trump the choice of the trump
	Bet playerBet; //Bet struct for the bat made


	/*********************************************/
    /****************Computation******************/
    /*********************************************/

	magenta(1);//prints in magenta
	printf("%s",titleAsciiArt);

	reset();//reset the color of prints
	printf("%s%s%s%s%s%s%s%s",lineAsciiArt,pointsAsciiArt,capotAsciiArt,generaleAsciiArt,coincheAsciiArt,surcoincheAsciiArt,pass,lineAsciiArt); //prints the menu

    printf("Your Hand is:\n");
	for(int i=0;i<(table[0]->hand_size);i++){ //for every card in the hand of the player
        printf("%c",valueArray[table[0]->Hand[i]->value]); //prints the value of the card from the array
        if(table[0]->Hand[i]->color == 'h'){ //if color is heart
            printf("%s ",HEART); //prints the heart symbol
        } else if(table[0]->Hand[i]->color == 's'){ //if color is spade
            printf("%s ",SPADE); //prints the spade symbol
        } else if(table[0]->Hand[i]->color == 'd'){ //if color is diamond
            printf("%s ",DIAMOND); //prints the diamond symbol
        } else { //else
            printf("%s ",CLUB); //prints the club symbol
        }
	}
    printf("\n");//jumps a line

	do{
		if (previousChoice.contract == 0){ //if the previous contract is an N number
			do {
				printf("There is no previous contract, so you can't coinche or surcoinche.\n"); //warn the player that there is no previous contract
				choice = verify(0,6); //asks the player his choice
			} while (choice == 5 || choice == 4);//do it until he doesn't choose coinche or surcoinche
		}
		else {
            printf("The previous contract has a value of %d and a trump of %c,\n",previousChoice.points,previousChoice.trump); //Prints the trump and the contract made by the previous player
            if (previousChoice.coinche==0 && previousChoice.team==2){ //if the previous player didn't coinched
                do {
                    printf("You can't surcoinche.\n"); //warn the player that he can't surcoinche
                    choice = verify(0,6); //asks the player his choice
                } while (choice == 5); //do it until he doesn't choose surcoinche
            } else if (previousChoice.coinche==1 || previousChoice.team==1) { // if the previous player coinched or if he passed
                do {
                    printf("You can't coinche.\n"); //warns the player he can't coinche again
                    choice = verify(0,6); //asks the player his choice
                } while (choice == 4); //do it until he doesn't choose coinche
            } else{
                printf("The player surcoinched so you can't bet"); //warns the player he can't bet
                return previousChoice; //return the previous bet
            }
		}

		switch(choice) { //do something depending on the value of choice

		case 1:
			do{
				printf("What is the value between 80 and 160 for n (only numbers dividable by 10)?\n"); // asks the player for the value of the contract
				number = verify(80,160); //asks the player a number
			}while((number>160 || number<80) || number%10 != 0); // do it until the number is dividable by 10
            playerBet.contract = choice; //the contract of the bet equals n points
			break;

		case 2:
			number = 250; //the value of the contract is 250
			playerBet.contract = choice;//the contract of the bet equals capot
			playerBet.coinche = 0;// there is no coinche or surcoinche
			break;

		case 3:
			number = 500; //the value of the contract is 500
			playerBet.contract = choice; //the contract of the bet equals general
			playerBet.coinche = 0;// there is no coinche or surcoinche
			break;

		case 4:
		    number = previousChoice.points*2; //the value of the contract is 2*previous bet
			playerBet.contract = previousChoice.contract; //the contract of the bet equals the previous bet
			playerBet.coinche = 1; // coinche is on
			break;
		case 5:
			number = previousChoice.points*2; //the value of the contract is 2*previous bet, so it is 4 times the contract of my ally
			playerBet.contract = previousChoice.contract; //the contract of the bet equals the previous bet
			playerBet.coinche = 2; // surcoinche is on
			break;

        case 6:
            return previousChoice; //pass you turn and return the previous bet

		}

        //asks the player which trump he wants
		printf("\nWhich Trump do you want ?\n");
		printf("1) %s \n",SPADE);
		printf("2) %s \n",HEART);
		printf("3) %s \n",CLUB);
		printf("4) %s \n",DIAMOND);
		printf("5) %s \n",ALLTRUMP);
		printf("6) %s \n",NOTRUMP);

		trump = verify(1,6); //gets the choice of the player

		switch(trump){ //does something depending on the trump chosen

        case 1:
            playerBet.trump = 's'; //trump is spade
            break;

        case 2:
            playerBet.trump = 'h'; //trump is heart
            break;

        case 3:
            playerBet.trump = 'c'; //trump is club
            break;

        case 4:
            playerBet.trump = 'd'; //trump is diamond
            break;

        case 5:
            playerBet.trump = 't'; //trump is all trump
            break;

        case 6:
            playerBet.trump = 'n'; //trump is no trump
            break;
		}

		if(previousChoice.points>number && choice != 6){ //if the chosen contract is worth less than the previous one, asks the player to choose a new one
			printf("You need to make an higher contract than the previous one or pass.\n\n");
		}
	} while(previousChoice.points>number && choice != 6);//do it until his contract is higher or he passes

	playerBet.points = number; //put the new value in bet
	playerBet.team = 1; // put the team number in the bet

	return playerBet;

}


/*
 * Makes the bet for the bots
 * @param table - dynamic array of players with their hand, hand size, etc.
 * @param previousChoice - bet type the previous bet with the contract, the team who made it, the value and if it is coinched or surcoinched
 * @param botNb - number of the player who is betting
 * @return the new bat made by the player
 */
Bet botBet(Player** table, Bet previousChoice, int botNb){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

    int nbH=0,nbS=0,nbC=0,nbD=0,max=0; //integer for the number of each color, and integer for the maximum
    int *hCards = (int*)malloc(sizeof(int)*8); //allocates a memory of 8 times an integer
    int *sCards = (int*)malloc(sizeof(int)*8); //allocates a memory of 8 times an integer
    int *cCards = (int*)malloc(sizeof(int)*8); //allocates a memory of 8 times an integer
    int *dCards = (int*)malloc(sizeof(int)*8); //allocates a memory of 8 times an integer
    Bet newBet;

    /*********************************************/
    /****************Computation******************/
    /*********************************************/

    if(botNb == 0){

        newBet = betMenu(table,previousChoice);
        return newBet;

    } else {

        for(int i=0;i<table[botNb]->hand_size;i++){ //for each card in the hand of the player

            if(table[botNb]->Hand[i]->color == 'h'){ //if its a heart
                hCards[nbH] = table[botNb]->Hand[i]->value; //add the value of the card in the array
                nbH ++; // plus one card in number of hearts
            } else if(table[botNb]->Hand[i]->color == 'd'){ //if its a diamond
                dCards[nbD] = table[botNb]->Hand[i]->value; //add the value of the card in the array
                nbD ++; // plus one card in number of diamond
            } else if(table[botNb]->Hand[i]->color == 'c'){ //if its a club
                cCards[nbC] = table[botNb]->Hand[i]->value; //add the value of the card in the array
                nbC ++; // plus one card in number of club
            } else {
                sCards[nbS] = table[botNb]->Hand[i]->value; //add the value of the card in the array
                nbS ++; // plus one card in number of spade
            }
        }

        nbH = howManyStrong(hCards, nbH, TRUE); // Puts the number of strong heart cards
        nbS = howManyStrong(sCards, nbS, TRUE); // Puts the number of strong spade cards
        nbD = howManyStrong(dCards, nbD, TRUE); // Puts the number of strong diamond cards
        nbC = howManyStrong(cCards, nbC, TRUE); // Puts the number of strong club cards

        max = (nbH > nbS ? nbH : nbS) > (nbD > nbC ? nbD : nbC) ? (nbH > nbS ? nbH : nbS) : (nbD > nbC ? nbD : nbC); // Find the maximum between the number of strong cards in every color

        free(hCards);
        free(dCards);
        free(cCards);
        free(sCards);

        if(max >= 3){ //if the maximum is greater or equals to 3
            if(max == 3 && previousChoice.points<80){ //if the maximum is equals to 3 and the bet points less than 80
                //makes a contract of 80 points
                newBet.contract = 1;
                newBet.points = 80;
                newBet.coinche = 0;
            } else if(max > 3 && previousChoice.points<120){ //if the maximum is greater than 3 and the bet points less than 120
                //makes a contract of 120 points
                newBet.contract = 1;
                newBet.points = 120;
                newBet.coinche = 0;
            }

            //puts the trump of the color with the maximum of strong cards
            if (max == nbH){
                newBet.trump = 'h';
            } else if (max == nbS){
                newBet.trump = 's';
            } else if (max == nbD){
                newBet.trump = 'd';
            } else {
                newBet.trump = 'c';
            }

            //set the teams who makes the bet depending on the bot
            if(botNb == 2){
                newBet.team = 1;
            } else{
                newBet.team = 2;
            }
            return newBet;
        } else { //else passes
            return previousChoice;
        }
    }
}


/*
 * Function that gives the number of strong card in a hand
 * @param cardColorValues - array of the values of all the card of one color
 * @param trump - the color a trump or not.
 * @return an integer representing the number of strong card from that color
 */
int howManyStrong(int* cardColorValues, int size, Boolean trump){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

    int strongCards=0; //initalize number of strong cards to 0

    /*********************************************/
    /****************Computation******************/
    /*********************************************/

    //adds one to strong cards if the card is a A,10,K or Q
    if(trump == FALSE){
        for(int i=0; i<size;i++){
            if(cardColorValues[i]>3){
                strongCards ++;
            }
        }
    //adds one to strong cards if the card is a A,10,J or 9
    } else {
        for(int i=0; i<size;i++){
            if(cardColorValues[i]>5 || (4>cardColorValues[i] && cardColorValues[i]>1)){
                strongCards ++;
            }
        }
    }

    return strongCards;

}
