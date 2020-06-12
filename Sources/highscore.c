/*
 * highscore.c
 *
 *  Created by William Mann
 */

#include <highscore.h>


/*
 * Gets the name typed by the user, verifies it.
 * @return a string, the name of the user
 */
char* playerCheck(){

	char* name = (char*)malloc(15*sizeof(char)); /* allocates a memory of size 15 times the size for a char type for the string 'name'*/
	strncpy(name,"",15); /* the program initializes the variable 'string' empty */
	int i = 0;/* initializes the integer i used for the iterations */
	boolean error = false; /* the boolean error used to tell if there's an error */

	/*Getting and verifying the name*/
		while(strlen(name) == 0){ /* while the length of the string 'name' equals zero: */
			printf("Enter you name for the score table:\n"); /*asks the user to enter their name;*/
			fflush(stdout); /* forces to empty the buffer, in other words, forces the printf to be shown; */
			fgets (name, 15, stdin); /* gets the string of 15 characters typed by the user on the keyboard and puts it in the variable 'name'; */
			while(error == false && i<strlen(name)-1){ /* while there is no error AND the variable 'i' is inferior to the length of the string in the variable 'name'-1; */
				if((0<=name[i] && name[i]<=44) || (47<=name[i] && name[i]<=64) || (91<=name[i] && name[i]<=96) || (123<=name[i] && name[i]<=255)){ /* if the letter in the place 'i' of the variable 'name' isn't a letter (if the ascii number or the vharacter isn't a min, maj letter or a - and a. ); */
					error = true; /* there is a error, so the variable 'error' is true; */
					printf("There is a forbidden character in your name : %c\n",name[i]); /* the program tells the user the first forbidden character; */
					strncpy(name,"",15); /* the program empties the variable 'string' */
				}
				i++; /* passing to the next letter; */
			}
			i = 0; /* new 'name', setting to the first letter; */
			error = false; /* new 'name', setting the 'error' to false; */
		}

		name[strlen(name)-1] = 0; /* erasing the last character of 'name', who is a \n */

		return name;
}


/*
 * Function that counts the lines in the file
 * @return the number of lines in the file
 */
int lineCount(){

	FILE* file = fopen("highscore.txt","r"); /* opens the file highscore.txt and reads it */
	int lines=0; /* initialize the lines integer to 0 */
	char chr; /* initialize the char variable chr */

	chr=getc(file); /* chr gets the first char of the file */
	while (chr != EOF){ /* while chr isn't the end of file:*/

		 if (chr == '\n'){ /*if ch is the character '\n':*/
	            lines = lines + 1; /* there is a line, so add a line to lines;*/
	     }
		 chr = getc(file); /* chr gets the next char of the file */
	}
	fclose(file); /* closes the file */
	return lines;

}



/*
 * Function that creates an array of highscores
 * @return the pointer to the  array of scores
 */
 highscore* scoreArray(int size){

	 FILE* file = fopen("highscore.txt","r");
	 int victories,loses;
	 char username[15];

	 highscore* scores = (highscore*) malloc(size * sizeof(highscore));

	 for(int i=0;i<size;i++){

		 fscanf(file,"%d,%d,%s\n",&victories,&loses,username);
		 scores[i].victories = victories;
		 scores[i].loses = loses;
		 strcpy(scores[i].name, username);

	 }
	 fclose(file);

	 return scores;
 }


 /*
  * Function that updates the score of a player
  */
 void scoreUpdate(highscore* scores, int size){

 	FILE* fileWrite = fopen("highscore.txt","w+");
 	int victories,loses;
 	char name[15];



 		for(int j=0; j<size; j++){
 			victories = scores[j].victories;
 			loses = scores[j].loses;
 			strcpy(name,scores[j].name);
 			fprintf(fileWrite,"%d,%d,%s\n",victories,loses,name);
 		}
 		fclose(fileWrite);
 }


/*
 * Gets and write the name and the score of the person in the file
 * @param
 */
void scoreWrite(boolean victory){

	/* creating a string of 15 characters and putting in the name checked thanks to the function playerCheck */
	char name[15];
	strcpy(name,playerCheck());

	int Player = -1,victories=0,loses=0,size=lineCount();

	FILE* file = fopen("highscore.txt","a");
	highscore* scores;

	scores = scoreArray(size);


	/*creating the array and verifying if the player is already in the Array*/
	for(int i=0; i<size; i++){
		if(strcmp(scores[i].name, name)==0){
			Player = i;
			printf("%d",Player);
			fflush(stdout);
		}
	}

	if(Player!=-1){
		if(victory == false){
			scores[Player].loses++;
		} else {
			scores[Player].victories ++;
		}
		scoreSorting(scores,size);
		scoreUpdate(scores,size);

	} else {
		if(victory == false){
			loses++;
		} else {
			victories++;
		}
		fprintf(file,"%d,%d,%s\n",victories,loses,name);
	}


	fclose(file);
}


/*
 * sort the scores from the highest to the lowest
 * @param scores - array of highscores
 * @param size - size of the array
 */
highscore* scoreSorting(highscore* scores, int size){

	highscore* sortedArray = (highscore*) malloc(size * sizeof(highscore));

	int victories, loses, position;
	char name[15];

	for(int i=1; i<size+1; i++){
		position = i;
		victories = scores[i].victories;
		loses = scores[i].loses;
		strcpy(name,scores[i].name);

		for(int j=i-1 ;j>0 ; j--){
			if(victories>scores[j].victories || (victories==scores[j].victories && loses<scores[j].loses)){
				swap(scores,position,j);
				position--;
			}
		}

	}

	sortedArray = scores;
	return sortedArray;
}

/**
 * Swap the two highscores at the indexes "index1" and "index2" in the array
 * @param scores - a array of highscores
 * @param index1 - an existing index in "myarray" to swap with "index2"
 * @param index2 - an existing index in "myarray" to swap with "index2"
 */
void swap(highscore* scores, int index1, int index2) {
	highscore swap;

	swap = scores[index1];
	scores[index1] = scores[index2];
	scores[index2] = swap;
}
