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
	for(int i = 0; i<5; i++){ //print the 5 best scores from the scoreArray
		printf("	%d	%d	%s\n",scores[i].victories,scores[i].loses,scores[i].name);
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
void clrscr(){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
       system("clear");
   #endif

   #if defined(_WIN32) || defined(_WIN64)
       system("cls");
   #endif
}
