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
 * Function that counts the lines in the file
 * @return the number of lines in the file
 */
int lineCount(){

	FILE* file = fopen("highscore.txt","r");
	int lines=0;
	char chr;

	chr=getc(file);
	while (chr != EOF){

		 if (chr == '\n'){
	            lines = lines + 1;
	     }
		 chr = getc(file);
	}
	fclose(file);
	return lines;

}


/*
 * Function that creates an array of highscores
 * @return the pointer to the  array of scores
 */
 highscore* scoreArray(){

	 FILE* file = fopen("highscore.txt","r");
	 int size = lineCount(), score;
	 char username[15];

	 highscore* scores = (highscore*) malloc(size * sizeof(highscore));

	 for(int i=0;i<size;i++){

		 fscanf(file,"%d,%s\n",&score,username);
		 scores[i].score = score;
		 strcpy(scores[i].name, username);

	 }


	 return scores;
 }


/*
 * Does a thing but idk yet
 */
void thing(){



}
