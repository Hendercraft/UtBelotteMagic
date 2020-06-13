/*
 * menu.c
 *
 *  Created by William Mann
 */

#include <menu.h>


/******************************************************************************/
/**************************FUNCTIONS BODIES*******************************/
/****************************************************************************/


/*
 * This series of protocol is used to print in color, but it only works if we are on specified OS
 */
void magenta (int bold){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	printf("\033[%d;35m",bold);
   	#endif
}
void reset(){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		printf("\033[0m)");
   	#endif

}
void green(int bold){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	printf("\033[%d;32m",bold);
   	#endif
}
void yellow(int bold){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		printf("\033[%d;33m",bold);
   	#endif
}
void blue(int bold){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		printf("\033[%d;34m",bold);
   	#endif
}
void red(int bold){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		printf("\033[%d;31m",bold);
   	#endif
}
void cyan (int bold){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
		printf("\033[%d;36m",bold);
   	#endif
}


/*
 * Function thats prints the Programm's menu in ASCII art.
 */
void menuVisual(){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

    // Strings of the art and text for the Main Menu
	char titleAsciiArt[]="\n ######   #######  #### ##    ##  ######  ##     ## ######## \n##    ## ##     ##  ##  ###   ## ##    ## ##     ## ##       \n##       ##     ##  ##  ####  ## ##       ##     ## ##       \n##       ##     ##  ##  ## ## ## ##       ######### ######   \n##       ##     ##  ##  ##  #### ##       ##     ## ##       \n##    ## ##     ##  ##  ##   ### ##    ## ##     ## ##       \n ######   #######  #### ##    ##  ######  ##     ## ######## \n";
	char lineAsciiArt[]="\n**--------------------------------------------------------**\n\n";
	char playAsciiArt[]="	1) Play\n";
	char scoreAsciiArt[]="	2) Highscores\n";
	char quitAsciiArt[]="	3) Quit\n";

	/*********************************************/
    /****************Computation******************/
    /*********************************************/

	magenta(1); // changes the text color to magenta(see the functions above)
	printf("%s",titleAsciiArt); // prints the title

	reset(); // resets the text color(see the functions above)
	printf("%s%s%s%s%s",lineAsciiArt,playAsciiArt,scoreAsciiArt,quitAsciiArt,lineAsciiArt); // prints the MainMenu
	fflush(stdout); //forces the buffer to synchronize, so the visuals are updated immediately

}


/*
 * Function thats prints the Highscore's menu in ASCII art.
 */
void scoreVisual(){


    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

    //strings of the art and text for the Highscore Menu
	char titleAsciiArt[]="\n ######   #######  #### ##    ##  ######  ##     ## ######## \n##    ## ##     ##  ##  ###   ## ##    ## ##     ## ##       \n##       ##     ##  ##  ####  ## ##       ##     ## ##       \n##       ##     ##  ##  ## ## ## ##       ######### ######   \n##       ##     ##  ##  ##  #### ##       ##     ## ##       \n##    ## ##     ##  ##  ##   ### ##    ## ##     ## ##       \n ######   #######  #### ##    ##  ######  ##     ## ######## \n";
	char lineAsciiArt[]="\n**--------------------------------------------------------**\n\n";
	char scoreAsciiArt[]="	VICTORIES/LOSES/NAME\n\n";
	char backAsciiArt[]="\n1) Back\n";
	char quitAsciiArt[]="2) Quit\n";

	int size = lineCount(); //counts the lines in the highscore file
	highscore* scores = scoreArray(size); //creates an array of scores from the highscore file


	/*********************************************/
    /****************Computation******************/
    /*********************************************/

	magenta(1); // changes the text color to magenta(see the functions above)
    printf("%s",titleAsciiArt); // prints the title

	reset(); // resets the text color(see the functions above)
	printf("%s%s",lineAsciiArt,scoreAsciiArt); // prints the line and subtitle

	if(scores == NULL){
        printf("There is no scores\n");
	} else {
	    for(int i = 0; i<5; i++){ //print the 5 best scores from the scoreArray
            printf("	%d	%d	%s\n",scores[i].victories,scores[i].loses,scores[i].name);
        }
	}

	printf("%s%s%s",backAsciiArt,quitAsciiArt,lineAsciiArt); //prints the rest of the highscore menu
	fflush(stdout); //forces the buffer to synchronize, so the visuals are updated immediately
}



/*
 * Function that asks and verifies if the entered string is a number between b and n, and if not, repeats itself.
 * @parameter b - integer min
 * @parameter n - integer max
 * @return a number between
 */
int verify(int b,int n){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

	char menuChoose[]="Please enter the number corresponding to your choice :\n";
	char userInput[3]; //string for the user input with a size of maximum 3 characters
	int number=-1; // initialization of number

    /*********************************************/
    /****************Computation******************/
    /*********************************************/

	printf("%s",menuChoose); //asks the user to enter a number
	fflush(stdout); //forces the buffer to synchronize, so the visuals are updated immediately
	while(number < b || number > n){ //while number is greater than n or smaller than b;
        printf("\a"); //makes a sound
		scanf("%s",userInput); // enables the user to enter something
		if (atoi(userInput) >= 0){ //if the number getting from the user is greater or equal to 0;
			number = atoi(userInput); // number takes the entered number
		}
	}
	return number;
}


/*
 * Function to clear the cmd, it changes the expression used in function of the OS
 */
void clrscr()
{
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
       system("clear");
   #endif

   #if defined(_WIN32) || defined(_WIN64)
       system("cls");
   #endif
}


/*
 * Function thats prints the ingame menu in ASCII art.
 * @param contract - the contract for this round
 * @param player - name of the player
 * @param falls - cards that have been played/cards in the fold
 * @param fallSize - size of the fold
 */
void ingameMenu(Bet contract, char* player, Player** table, Card** falls, int fallsSize){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

    //allocates the places for the printing of the players played cards, the reump, the contract
    char* cardNorth = (char*)malloc(2*sizeof(char));
    char* cardWest = (char*)malloc(2*sizeof(char));
    char* cardEast = (char*)malloc(2*sizeof(char));
    char* cardPlayer = (char*)malloc(2*sizeof(char));
    char* trumpColor = (char*)malloc(10*sizeof(char));
    char* currentContract = (char*)malloc(25*sizeof(char));
    //creates variables for the value of the contract and the players hand
    char Value[] = "";
    char cardsHand[] = "";
    //table to convert the values of the cards in char
    char realValue[8]={'7','8','9','J','Q','K','X','A'};
    //initializing the played cards to none
    strcpy(cardNorth,"");
    strcpy(cardWest,"");
    strcpy(cardEast,"");
    strcpy(cardPlayer,"");


    /*********************************************/
    /****************Computation******************/
    /*********************************************/

    switch(contract.contract){ //does something depending on the contract

    case 1: //if its the first contract
        if(contract.coinche==0){ //if not coinched, prints N points with N the value of the contracts
            snprintf(currentContract,sizeof(char)*25,"%d",contract.points); // prints the number in the variable currentContract as string
            strcat(currentContract," Points");
        } else if(contract.coinche==1){ //if coinched, prints N points (Coinched) with N the value of the contracts
            snprintf(currentContract,sizeof(char)*25,"%d",contract.points); // prints the number in the variable currentContract as string
            strcat(currentContract," Points (coinched)");
        } else { //if surcoinched, prints N points (Surcoinched) with N the value of the contracts
            snprintf(currentContract,sizeof(char)*25,"%d",contract.points);// prints the number in the variable currentContract as string
            strcat(currentContract," Points (surcoinched)");
        }

        break;

    case 2: //if its the second contract
        //the same as case 1 but with Capot
        if(contract.coinche==0){
            strcat(currentContract,"Capot");
        } else if(contract.coinche==1){
            strcat(currentContract,"Capot (coinched)");
        } else {
            strcat(currentContract,"Capot (surcoinched)");
        }
        break;

    case 3: //if its the third contract
        //the same as case 1 but with General
        if(contract.coinche==0){
            strcat(currentContract,"General");
        } else if(contract.coinche==1){
            strcat(currentContract,"General (coinched)");
        } else {
            strcat(currentContract,"General (surcoinched)");
        }
        break;
    }

    for(int i=0; i<fallsSize;i++){ //for every card played
        //adds the value of the card in the variable
        Value[0] = realValue[falls[i]->value];
        Value[1] = '\0';
        if(falls[i]->player == 1){ //if its from the player, it puts it in the player variable with the color
            strcpy(cardPlayer,Value);
            strcat(cardPlayer,colorToString(falls[i]->color));
        } else if(falls[i]->player == 2){//if its from West, it puts it in the West variable with the color
            strcpy(cardWest,Value);
            strcat(cardWest,colorToString(falls[i]->color));
        } else if(falls[i]->player == 3){//if its from North, it puts it in the North variable with the color
            strcpy(cardNorth,Value);
            strcat(cardNorth,colorToString(falls[i]->color));
        } else {//if its from North, it puts it in the North variable with the color
            strcpy(cardEast,Value);
            strcat(cardEast,colorToString(falls[i]->color));
        }
    }


    strcpy(trumpColor,colorToString(contract.trump)); // puts the color string of the trump in the trump color

    //prints the menu
    printf("                     You are team 1\n\n                         North\n\n                          %s\n\n\n           West  %s                   %s  East\n\n\n                          %s\n\n                        %s\n\n",cardNorth,cardWest,cardEast,cardPlayer,player);
    printf("Trump is : %s       Current contract : %s for team %d",trumpColor,currentContract,contract.team);
    printf("\n**---------------------------------------------------------------------**\n");
    printf("Your cards are :\n");

    //prints the card in the players hand
    for(int j=0; j<table[0]->hand_size;j++){
        cardsHand[0] = realValue[table[0]->Hand[j]->value];
        cardsHand[1] = '\0';
        strcat(cardsHand,colorToString(table[0]->Hand[j]->color));
        printf("%d) %s   ",j+1,cardsHand);
    }
    printf("\n\n");

}


/*
 * Function that transform a character of the color into the symbol
 * @param color - first letter of the color
 * @return the string of the character symbol
 */
char* colorToString(char color){

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

    char* colorString = (char*)malloc(sizeof(char)*10); // allocating in memory 10 times the size of an character for the colorString

    //assign the string of the symbol, depending on the color asked.
    if(color=='c'){
        strcpy(colorString,CLUB);
    } else if(color=='d'){
        strcpy(colorString,DIAMOND);
    } else if(color=='s'){
        strcpy(colorString,SPADE);
    } else if(color=='h'){
        strcpy(colorString,HEART);
    } else if(color=='n'){
        strcpy(colorString,NOTRUMP);
    } else {
        strcpy(colorString,ALLTRUMP);
    }

    return colorString;

}


