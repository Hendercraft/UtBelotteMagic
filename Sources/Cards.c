#include <Cards.h>

void cardsdeal(Player** table,Card** deck,int dealerid){

	int whosecard[7] = {0,1,2,3,0,1,2}; // cheap trick that avoid me writing some if
	int iterable1=0, iterable2=0, iterable3=0 ,iterable4 = 0;


	for (int i=0;i<32;i++){  //Parcouring the whole deck to deal it to players

		if ((deck[i]->position <=3) || (deck[i]->position >=13 && deck[i]->position <=14) || (deck[i]->position >=21 && deck[i]->position <=23)){ //Cards of the player at the left of the dealer
			table[whosecard[dealerid]]->Hand[iterable1] = deck[i];
			deck[i]->player = whosecard[dealerid] + 1;
			iterable1++;

		}else if ((deck[i]->position >=4 && deck[i]->position <=6) || (deck[i]->position >=15 && deck[i]->position <=16) || (deck[i]->position >=24 && deck[i]->position <=26)){ //Cards of the player in fort of the dealer

			table[whosecard[dealerid+1]]->Hand[iterable2] = deck[i];
			deck[i]->player = whosecard[dealerid+1] + 1;
			iterable2++;


		} else if ((deck[i]->position >=7 && deck[i]->position <=9) || (deck[i]->position >=17 && deck[i]->position <=18) || (deck[i]->position >=27 && deck[i]->position <=29)){ //Cards of the player at the left of the dealer

			table[whosecard[dealerid+2]]->Hand[iterable3] = deck[i];
			deck[i]->player = whosecard[dealerid+2] + 1;
			iterable3++;

		}else{ //Cards of the player who's dealing

			table[dealerid-1]->Hand[iterable4] = deck[i];
			deck[i]->player = dealerid;
			iterable4++;
		}
	}return;
}








Player* createplayer(){
	Player* table = (Player*) malloc(4 * sizeof(Player));
	if (table != NULL){
		for (int i=0; i<4; i++){
			table[i].id = i+1;
			table[i].bet = 0;
			table[i].hand_size = 8;
			table[i].Hand = (Card**)malloc(sizeof(Card*)*8);
			for(int j=0; j<8;j++) {
				table[i].Hand[i] = NULL;
			}
		}
	}else{
		fprintf( stderr, "there is an error with the memory allocation for the array of Player");
		return NULL;
	}
	return table;
}


Card* createcards(){
	Card* deck = (Card*) malloc(32 * sizeof(Card)); //allocating the memory
	char* color = "hcds"; // I'll iterate over it to define the color
	if (deck != NULL){
		for (int i=0; i<4; i++){  // Color's loop, each new loop mean a new color, first will be heart than club, diamond and spade
			for (int value=0; value<8;value++){ //Value's loop, each new loop mean a new card

				deck[value+8*i].value=value; // 7 Being the ace, 6 the 10, 5 the king.... 0 the 7
				deck[value+8*i].color=color[i];
				deck[value+8*i].player=0;
				deck[value+8*i].trump=0;
				deck[value+8*i].position= (i)*8+(value+1);
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
	if (nbxtrump > 0){ //if at least one trump has been found
		player = whowintrump(fallstrump,nbxtrump); // Use the fonction with the trump order
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

	return player; //I'll retrun the Id of the player who won the split
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
