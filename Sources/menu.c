/*
 * menu.c
 *
 *  Created by William Mann
 */

#include <menu.h>


/*This series of protocol just set the output color */

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

	char titleAsciiArt[]="\n ######   #######  #### ##    ##  ######  ##     ## ######## \n##    ## ##     ##  ##  ###   ## ##    ## ##     ## ##       \n##       ##     ##  ##  ####  ## ##       ##     ## ##       \n##       ##     ##  ##  ## ## ## ##       ######### ######   \n##       ##     ##  ##  ##  #### ##       ##     ## ##       \n##    ## ##     ##  ##  ##   ### ##    ## ##     ## ##       \n ######   #######  #### ##    ##  ######  ##     ## ######## \n";
	char lineAsciiArt[]="\n**--------------------------------------------------------**\n\n";
	char playAsciiArt[]="	1) Play\n";
	char scoreAsciiArt[]="	2) Highscores\n";
	char quitAsciiArt[]="	3) Quit\n";

	magenta(1);
	printf("%s",titleAsciiArt);

	reset();
	printf("%s%s%s%s%s",lineAsciiArt,playAsciiArt,scoreAsciiArt,quitAsciiArt,lineAsciiArt);
	fflush(stdout);

}


/*
 * Function thats prints the Highscore's menu in ASCII art.
 */
void scoreVisual(){

	char titleAsciiArt[]="\n ######   #######  #### ##    ##  ######  ##     ## ######## \n##    ## ##     ##  ##  ###   ## ##    ## ##     ## ##       \n##       ##     ##  ##  ####  ## ##       ##     ## ##       \n##       ##     ##  ##  ## ## ## ##       ######### ######   \n##       ##     ##  ##  ##  #### ##       ##     ## ##       \n##    ## ##     ##  ##  ##   ### ##    ## ##     ## ##       \n ######   #######  #### ##    ##  ######  ##     ## ######## \n";
	char lineAsciiArt[]="\n**--------------------------------------------------------**\n\n";
	char scoreAsciiArt[]="	VICTORIES/LOSES/NAME\n\n";
	char backAsciiArt[]="\n1) Back\n";
	char quitAsciiArt[]="2) Quit\n";

	int size = lineCount();
	highscore* scores = scoreArray(size);

	magenta(1);
	printf("%s",titleAsciiArt);

	reset();
	printf("%s%s",lineAsciiArt,scoreAsciiArt);
	for(int i = 0; i<5; i++){
		printf("	%d	%d	%s\n",scores[i].victories,scores[i].loses,scores[i].name);
	}
	printf("%s%s%s",backAsciiArt,quitAsciiArt,lineAsciiArt);
	fflush(stdout);
}



/*
 * Function that verifies if the is a number between 0 and n
 * @parameter n - integer max
 * @return a number
 */
int verify(int n){

	char menuChoose[]="Please enter the number corresponding to your choice :\n";
	char userInput[1];
	int number=-1;

	printf("%s",menuChoose);
	fflush(stdout);
	while(number <= 0 || number > n){
		scanf("%c",userInput);
		if (atoi(userInput) != 0){
			number = atoi(userInput);
		}
	}
	return number;
}


/*
 * Function to clear the cmd
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
