/*
 * bet.c
 *
 *  Created by William Mann
 */

#include <bet.h>


int* betMenu(Player** table, int* previousChoice){

	char titleAsciiArt[]="\n########  ######## ########  ######\n##     ## ##          ##    ##    ##\n##     ## ##          ##    ##\n########  ######      ##     ######\n##     ## ##          ##          ##\n##     ## ##          ##    ##    ##\n########  ########    ##     ######\n";
	char lineAsciiArt[]="\n**---------------------------------------------------------------------------**\n\n";
	char pointsAsciiArt[]="	1) N points - Your teams gets a minimum of N points\n";
	char capotAsciiArt[]="	2) Capot - Your teams must win all folds\n";
	char generaleAsciiArt[]="	3) Générale - You must win all folds\n";
	char coincheAsciiArt[]="	4) Coinche - The before stated contract cannot be full filled\n";
	char surcoincheAsciiArt[]="	5) Surcoinche - The coinched contract can be full filled\n";
	char pass[]="	6) Pass\n";

	int choice,number=0;
	int* bet = (int*)malloc(2*sizeof(int));

	magenta(1);
	printf("%s",titleAsciiArt);

	reset();
	printf("%s%s%s%s%s%s%s%s",lineAsciiArt,pointsAsciiArt,capotAsciiArt,generaleAsciiArt,coincheAsciiArt,surcoincheAsciiArt,pass,lineAsciiArt);

	do{
		printf("The previous contract has a value of %d,\n",previousChoice[1]);
		if (previousChoice[0] == 0){
			do {
				printf("There is no previous contract, so you can't coinche or surcoinche.\n");
				choice = verify(0,6);
			} while (choice == 5 || choice == 4);
		}
		else if(previousChoice[0] == 4){
			do {
				printf("There is a coinche so you can't coinche again.\n");
				choice = verify(0,6);
			} while (choice == 4);
		}
		else {
			do {
				printf("You can't surcoinche.\n");
				choice = verify(0,6);
			} while (choice == 5);
		}

		switch(choice) {

		case 1:
			do{
				printf("What is the value between 80 and 160 for n ?\n");
				number = verify(80,160);
			}while(number>160 || number<80);
			break;

		case 2:
			number = 250;
			break;

		case 3:
			number = 500;
			break;

		case 4:
		case 5:
			number = previousChoice[1]*2;
			break;

		}

		if(previousChoice[2]>number){
			printf("You need to make an higher contract than the previous one or pass.\n");
		}
	} while(previousChoice[2]>number);


	bet[0] = choice;
	bet[1] = number;

	return bet;


}
