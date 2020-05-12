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
void scoreWrite(int score){

	char name[15]="";
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

	fprintf(file,"%d,%s",score,name);
	fclose(file);
}


/*
 * Does a thing but idk yet
 */
void thing(){



}
