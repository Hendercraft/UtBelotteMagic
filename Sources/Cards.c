#include <Cards.h>

Card* creatcards(){
	Card* deck = (Card*) malloc(32 * sizeof(Card)); //allocating the memory
	char* color = "hcds"; // I'll itertate over it to define the color
	if (deck != NULL){
		for (int i=0; i<4; i++){  // Color's loop, each new loop mean a new color, first will be Heart than club, diamond and spade
			for (int value=0; value<8;value++){ //Value's loop, each new loop mean a new card
			
				deck[value+8*i].value=value; // 7 Being the ace, 6 the 10, 5 the king.... 0 the 7
				deck[value+8*i].color=color[i];
				deck[value+8*i].player=0;
				deck[value+8*i].trump=0;
				deck[value+8*i].position= (i+1)*8+(value+1);
			}
		}
		return deck;
	}
	else {
		fprintf( stderr, "there is an error with the memory allocation for the array of Cards");
		return NULL;
	}
}



int Endofturn(Card** falls){
	int nbxtrump = 0;
/*Parsing the array to know if there's any trump*/
	Card* fallstrump = NULL;
	for (int i=0; i<4; i++){
		if (falls[i]->trump == 1 ){ //If so, I stock them in another array
			if (nbxtrump == 0){
				fallstrump = (Card*) malloc(sizeof(Card));
			} else {
				fallstrump = (Card*) realloc(fallstrump,sizeof(Card)*(nbxtrump+1));
			}
			if (fallstrump != NULL){
				fallstrump[nbxtrump] = *falls[i];
				nbxtrump++;
			}else{
				fprintf( stderr, "there is an error with the memory allocation for the trumarray in the Endofturn function");
				return 0;
			}
		}
	}
	
	int player = 0;
	if (nbxtrump > 0){ 
		player = whowintrump(fallstrump,nbxtrump);
		free(fallstrump);
		fallstrump = NULL;
	}else{
		player = whowin(*falls);
	}

	int winteam = 0;
	if ((player == 1) || (player == 3)){ //If the winner is South or North
		 winteam = -1; // We will put all the card in team 1 fold
	}else{
		winteam = -2;
	}
	for (int i=0;i<4;i++){
		falls[i]->player = winteam;
	}
	
	return player;
}


int whowin(Card* falls){
	int max = falls[0].value;
	int indexmax = 0;	 
	for (int i=1 ;i<4;i++){
		if (falls[i].color == falls[0].color) {
			if (max<falls[i].value){
				max = falls[i].value;
				indexmax = i;
			}
		}
	}
	return falls[indexmax].player;
}

int whowintrump(Card* fallstrump, int size){
	int order[8] = {0,1,6,7,2,3,4,5}; // Trump order
	int max = order[fallstrump[0].value];
	int indexmax = 0;
	for (int i=1; i<size; i++){
		if (max<order[fallstrump[i].value]){
			max = order[fallstrump[i].value];
			indexmax = i;
		}
	}
	return fallstrump[indexmax].player;
}
