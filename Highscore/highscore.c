/*
 * highscore.c
 *
 *  Created by William Mann
 */

#include <highscore.h>

/*
 * Checks if the highscore.txt file is present, if not it creates it
 */
void fileCheck(){

	FILE* file = fopen("highscore.txt","r");
	if ( file == 0){
		printf("error, no file found\ncreating file...\n");
		fflush(stdout);
		fopen("highscore.txt","w");
		printf("File created !\n");
		fflush(stdout);
	} else {
		printf("There is a file ! Welcome back !\n");
		fflush(stdout);
	}
	fclose(file);

}

/*
 * Gets and write the name and the score of the person in the file
 */
void scoreWrite(){

	char name[15]="",score[4]="0",gameScore[19];
	int i=0,error=0;
	FILE* file = fopen("highscore.txt","a");

	/*Getting and verifying the name*/
	while(strlen(name) == 0){
		printf("Enter you name for the score table:\n");
		fflush(stdout);
		fgets (name, 15, stdin);
		while(error == 0 && i<strlen(name)-1){
			if((0<=name[i] && name[i]<=44) || (47<=name[i] && name[i]<=64) || (91<=name[i] && name[i]<=96) || (123<=name[i] && name[i]<=255)){
				error = 1;
				printf("There is a forbidden character in your name : %c\n",name[i]);
				strncpy(name,"",15);
			}
			i++;
		}
		i=0;
		error=0;
	}

	/*Creating the players highscore for the text file and writing it*/
	strcpy(gameScore,score);
	strcat(gameScore," ");
	strcat(gameScore,name);
	fprintf(file,gameScore);
	fclose(file);
}
/*
 * Sort the file from the best to the worst score, and erase the worst one if there is 2 same names
 */
void scoreSort(){

	FILE* scoreFileRead = fopen("highscore.txt","r");
	FILE* scoreFileWrite = fopen("highscore.txt","w");
	FILE* tempFile = fopen("temporary.txt","w");
	int lines=0;
	char ch;

	/*Count lines in the file highscore*/
	while(feof(scoreFile)==0){
		ch = fgetc(scoreFileRead);
		  if(ch == '\n')
		  {
		    lines++;
		  }
	}

	printf("%d",lines);
	fflush(stdout);

	fclose(scoreFile);
	fclose(tempFile);
	remove("temporary.txt");

}
