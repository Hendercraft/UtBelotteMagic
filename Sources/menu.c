/*
 * menu.c
 *
 *  Created by William Mann
 */

#include <menu.h>

/*
 * Function thats prints the Programm's menu in ASCII art.
 */
void menuVisual(){

	char titleAsciiArt[]="\n ######   #######  #### ##    ##  ######  ##     ## ######## \n##    ## ##     ##  ##  ###   ## ##    ## ##     ## ##       \n##       ##     ##  ##  ####  ## ##       ##     ## ##       \n##       ##     ##  ##  ## ## ## ##       ######### ######   \n##       ##     ##  ##  ##  #### ##       ##     ## ##       \n##    ## ##     ##  ##  ##   ### ##    ## ##     ## ##       \n ######   #######  #### ##    ##  ######  ##     ## ######## \n";
	char lineAsciiArt[]="\n**--------------------------------------------------------**\n\n";
	char playAsciiArt[]="	1) Play\n";
	char scoreAsciiArt[]="	2) Highscores\n";
	char quitAsciiArt[]="	3) Quit\n";

	printf("%s%s%s%s%s%s",titleAsciiArt,lineAsciiArt,playAsciiArt,scoreAsciiArt,quitAsciiArt,lineAsciiArt);
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
