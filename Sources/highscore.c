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

    fseek (file, 0, SEEK_END); //gets to the end of the file
    sizeFile = ftell(file); //get the file position

    if (0 == sizeFile) { //if the file is empty

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

	int Player = -1,victories=0,loses=0,size=lineCount(); //integer for the place of the player, the number of victories, the number of loses and the number of lines in the file

	FILE* file = fopen("highscore.txt","a"); //open highscore in adding
	highscore* scores; //creates an array of scores

	scores = scoreArray(size); // fulls the array with the scores in the file

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
    //if the player exists in the file
	if(Player!=-1){
        //adds the lose or victories for the new player
		if(victory == FALSE){
			scores[Player].loses++;
		} else {
			scores[Player].victories ++;
		}
        //sorts and updates the array
		scoreSorting(scores,size);
		scoreUpdate(scores,size);

	} else { //if he doesn't exist
	    //adds a victory or a loss
		if(victory == FALSE){
			loses++;
		} else {
			victories++;
		}
		//adds the player
		fprintf(file,"%d,%d,%s\n",victories,loses,name);
	}


	fclose(file); //closes the file
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

	highscore* sortedArray = (highscore*) malloc(size * sizeof(highscore)); //creates an array of highscore as great as the number of lines in the file

	int victories, loses, position; // integer for victories loses and the position of the player
	char name[15]; //string for the name of the player

	/*********************************************/
    /****************Computation******************/
    /*********************************************/

	for(int i=1; i<size+1; i++){ // for every entity in the array
		position = i;
		victories = scores[i].victories; //victories takes the victory of player i
		loses = scores[i].loses; //loses takes the lose of player i
		strcpy(name,scores[i].name); //name takes the name of player i

		for(int j=i-1 ;j>0 ; j--){ //for every highscore before in the array
            // if he has more victories and less loses swap the two arrays
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

	highscore swap;

	/*********************************************/
    /****************Computation******************/
    /*********************************************/

	swap = scores[index1];
	scores[index1] = scores[index2];
	scores[index2] = swap;
}


int* teamFoldPoints(Card** deck, Bet contract){

    int* teampoints = (int*)malloc(sizeof(int)*2);
    int trump[8] = {0,0,14,20,3,4,10,11};
    int nottrump[8] = {0,0,0,2,3,4,10,11};
    int allTrump[8] = {0,0,9,14,1,3,5,6};
    int noTrump[8] = {0,0,0,2,3,4,10,19};

    teampoints[0] = 0;
    teampoints[1] = 0;

    if(contract.trump == 't'){
        for(int i=0;i<32;i++){
            if(deck[i]->player==1 || deck[i]->player==3){
                teampoints[0] += allTrump[deck[i]->value];
            }
        }
    } else if(contract.trump == 'n'){
        for(int i=0;i<32;i++){
            if(deck[i]->player==1 || deck[i]->player==3){
                teampoints[0] += noTrump[deck[i]->value];
            }
        }
    } else {
        for(int i=0;i<32;i++){
            if(deck[i]->trump==TRUE){
                if(deck[i]->player==1 || deck[i]->player==3){
                    teampoints[0] += trump[deck[i]->value];
                }
            } else {
                if(deck[i]->player==1 || deck[i]->player==3){
                    teampoints[0] += nottrump[deck[i]->value];
                }
            }
        }
    }

    teampoints[1] = 152 - teampoints[0];

    return teampoints;

}


 int* scoreCount(Bet contract, Card** deck){

    Boolean contractValid;
    int scoreAttack,scoreDefense,player1=0,player2=0,teamDer,pointGoes;
    int* teamPoints = (int*)malloc(sizeof(int)*2);
    teamPoints = teamFoldPoints(deck, contract);

    for(int i=0; i<32;i++){

        if(deck[i]->position==32){
            printf("%c %d",deck[i]->color,deck[i]->value);
            if(deck[i]->player == -1 || deck[i]->player == -3){
                teamDer = 1;
            } else {
                teamDer = 2;
            }
        }

        if(contract.team == 0 || contract.team == 2){

            if(deck[i]->player==-1){
                player1 ++;
            } else if(deck[i]->player==-3){
                player2 ++;
            }

        } else if(contract.team == 1 || contract.team == 3){

            if(deck[i]->player==-2){
                player1 ++;
            } else if(deck[i]->player==-4){
                player2 ++;
            }

        }
    }
    if(player1+player2 == 32){
        if(player1 == 32 || player2 == 32){
            contract.contract = 3;
            contract.points = 500;
            contractValid = TRUE;
        } else {
            contract.contract = 2;
            contract.points = 250;
            contractValid = TRUE;
        }
    } else {
        if(contract.team == 1 || contract.team == 3){
            pointGoes = 1;
        } else {
            pointGoes = 0;
        }
        contractValid = teamPoints[pointGoes] > contract.points ? TRUE : FALSE;
    }


    if(contractValid == TRUE){

        if(contract.team == 0 || contract.team == 2){
                if(contract.coinche == 0){

                    scoreAttack = teamPoints[0] + contract.points;
                    scoreDefense = teamPoints[1];
                    if(teamDer == 1){
                        scoreAttack += 10;
                    } else {
                        scoreDefense += 10;
                    }

                } else {

                    scoreAttack = (teamPoints[0] + contract.points)*2*contract.coinche;
                    scoreDefense = 0;

                }

        } else {

                if(contract.coinche == 0){

                    scoreAttack = teamPoints[1] + contract.points;
                    scoreDefense = teamPoints[0];
                    if(teamDer == 2){
                        scoreAttack += 10;
                    } else {
                        scoreDefense += 10;
                    }

                } else {

                    scoreAttack = (teamPoints[1] + contract.points)*2*contract.coinche;
                    scoreDefense = 0;

                }
        }

    } else {

        if(contract.team == 0 || contract.team == 2){
                if(contract.coinche == 0){

                    scoreAttack = teamPoints[0] + contract.points;
                    scoreDefense = teamPoints[1];
                    if(teamDer == 1){
                        scoreAttack += 10;
                    } else {
                        scoreDefense += 10;
                    }

                } else {

                    scoreAttack = (teamPoints[0] + contract.points)*2*contract.coinche;
                    scoreDefense = 0;

                }

        } else {

                if(contract.coinche == 0){

                    scoreAttack = 0;
                    scoreDefense = 162+contract.points;

                } else {

                    scoreAttack = 0;
                    scoreDefense = (162+contract.points)*2*contract.coinche;

                }
        }
    }

    if(contract.team == 0 || contract.team == 2){
        teamPoints[0]=scoreAttack;
        teamPoints[1]=scoreDefense;
    } else {
        teamPoints[1]=scoreAttack;
        teamPoints[0]=scoreDefense;
    }

    return teamPoints;

 }
