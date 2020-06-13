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

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

	char* name = (char*)malloc(15*sizeof(char)); /* allocates a memory of size 15 times the size for a char type for the string 'name'*/
	strncpy(name,"",15); /* the program initializes the variable 'string' empty */
	int i = 0;/* initializes the integer i used for the iterations */
	Boolean error = FALSE; /* the boolean error used to tell if there's an error */

	/*********************************************/
    /****************Computation******************/
    /*********************************************/

	/*Getting and verifying the name*/
		while(strlen(name) == 0){ /* while the length of the string 'name' equals zero: */
			printf("Enter you name for the score table:\n"); /*asks the user to enter their name;*/
			fflush(stdout); /* forces to empty the buffer, in other words, forces the printf to be shown; */
			fgets (name, 15, stdin); /* gets the string of 15 characters typed by the user on the keyboard and puts it in the variable 'name'; */
			while(error == FALSE && (i == 0 || i<strlen(name)-1)){ /* while there is no error AND the variable 'i' is inferior to the length of the string in the variable 'name'-1; */
				if((0<=name[i] && name[i]<=44) || (47<=name[i] && name[i]<=64) || (91<=name[i] && name[i]<=96) || (123<=name[i] && name[i]<=255)){ /* if the letter in the place 'i' of the variable 'name' isn't a letter (if the ascii number or the vharacter isn't a min, maj letter or a - and a. ); */
					error = TRUE; /* there is a error, so the variable 'error' is true; */
					clrscr();
					strncpy(name,"",15); /* the program empties the variable 'string' */
				}
				i++; /* passing to the next letter; */
			}
			i = 0; /* new 'name', setting to the first letter; */
			error = FALSE; /* new 'name', setting the 'error' to false; */
		}

		name[strlen(name)-1] = 0; /* erasing the last character of 'name', who is a \n */

		return name;
}


/*
 * Function that counts the lines in the file
 * @return the number of lines in the file
 */
int lineCount(){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

	FILE* file = fopen("highscore.txt","r"); /* opens the file highscore.txt and reads it */
	int lines=0; /* initialize the lines integer to 0 */
	char chr; /* initialize the char variable chr */

	/*********************************************/
    /****************Computation******************/
    /*********************************************/

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
 * Function that creates an array of highscores from the highscore file
 * @return the pointer to the  array of scores
 */
 highscore* scoreArray(int size){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

	 FILE* file = fopen("highscore.txt","r"); // opens the file highscore.txt
	 int victories,loses,sizeFile; // integers for the victories and loses of a player and the size of the file
	 char username[15]; // string of 15 characters for the name of the player
	 highscore* scores = (highscore*) malloc(size * sizeof(highscore)); //creates an array or scores of the size size

    /*********************************************/
    /****************Computation******************/
    /*********************************************/

    fseek (file, 0, SEEK_END);
    sizeFile = ftell(file);

    if (0 == sizeFile) {

        return NULL;

    } else {

         for(int i=0;i<size;i++){ //for each line in the file,

             fscanf(file,"%d,%d,%s\n",&victories,&loses,username); // puts the first integer in victories, the second one in losses and the string in username
             scores[i].victories = victories; // puts the number of victories in the array at place i
             scores[i].loses = loses; // puts the number of loses in the array at place i
             strcpy(scores[i].name, username); // puts the username in the array at place i

         }
    }

    fclose(file); // closes the file

    return scores;
 }


 /*
  * Function that updates the scores in the file
  */
 void scoreUpdate(highscore* scores, int size){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

 	FILE* fileWrite = fopen("highscore.txt","w+"); //open the file highscore.txt file in writing mode
 	int victories,loses; // integers for the victories and loses of a player
 	char name[15]; // string of 15 characters for the name of the player

    /*********************************************/
    /****************Computation******************/
    /*********************************************/

    for(int j=0; j<size; j++){ //for each line in the file,
        victories = scores[j].victories; //victories take the value of the victories of the place j in the array
        loses = scores[j].loses; //loses take the value of the loses of the place j in the array
        strcpy(name,scores[j].name); //name take the string of the name of the place j in the array
        fprintf(fileWrite,"%d,%d,%s\n",victories,loses,name); //writes in the files the victories,lose and name of a user in the format; v,l,name.
    }
    fclose(fileWrite);//closes the file
 }


/*
 * Gets and write the name and the score of the person in the file
 * @param
 */
void scoreWrite(Boolean victory){

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

	/* creating a string of 15 characters and putting in the name checked thanks to the function playerCheck */
	char name[15];
	strcpy(name,playerCheck());

	int Player = -1,victories=0,loses=0,size=lineCount();

	FILE* file = fopen("highscore.txt","a");
	highscore* scores;

	scores = scoreArray(size);

	/*********************************************/
    /****************Computation******************/
    /*********************************************/


	/*creating the array and verifying if the player is already in the Array*/
	for(int i=0; i<size; i++){
		if(strcmp(scores[i].name, name)==0){
			Player = i;
			printf("%d",Player);
			fflush(stdout);
		}
	}

	if(Player!=-1){
		if(victory == FALSE){
			scores[Player].loses++;
		} else {
			scores[Player].victories ++;
		}
		scoreSorting(scores,size);
		scoreUpdate(scores,size);

	} else {
		if(victory == FALSE){
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

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

	highscore* sortedArray = (highscore*) malloc(size * sizeof(highscore));

	int victories, loses, position;
	char name[15];

	/*********************************************/
    /****************Computation******************/
    /*********************************************/

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

    /*********************************************/
    /*****************VARIABLES*******************/
    /*********************************************/

	highscore swap; //

	/*********************************************/
    /****************Computation******************/
    /*********************************************/

	swap = scores[index1];
	scores[index1] = scores[index2];
	scores[index2] = swap;
}


int* teamFoldPoints(Card** deck, Bet contract){

    /*int teampoints[2] = {0,0};
    int trump[8] = {20,14,11,10,4,3,0,0};
    int nottrump[8] = {11,10,4,3,2,0,0,0};
    int allTrump[8] = {14,9,6,5,3,1,0,0};
    int noTrump[8] = {19,10,4,3,2,0,0,0};

    if(contract.trump == 't'){
        for(int i=0;i<32;i++){
            if(deck[i]->player==-1 || deck[i]->player==-3){
                teampoints[1] += deck->value[i];
            } else {
                teampoints[2] += deck->value[i];
            }
        }
    }*/

}


 /*
  * Counts the score of the team
  */
 int scoreCount(Bet contract, int foldPoints, Boolean belote, Boolean der){

/*    Boolean contractValid;
    int scoreAttack,scoreDefense;

    if(contract.contract == 1){
        contractValid = foldPoints > contract.points ? TRUE : FALSE;
    }

    if(contractValid == TRUE){
        switch(contract.coinche){
        }
        scoreAttack = foldPoints + contract.points;
        scoreDefense = 152-foldPoints;
    }*/
 }
