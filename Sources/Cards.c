
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

void definetrump(Card** deck,char trump){
	for (int i=0; i<32; i++){
		if (deck[i]->color == trump){
			deck[i]->trump = TRUE;
		}
	}
	return;
}
	

int* checkcard(Player** table,Card** falls,int playerid,int sizefalls){
/*This funtion is definitly one of the hardest to read
 i'm pretty sure there's way to improve it by a lot
 but for now we'll stick with it because at least it works*/

	int maxtrump = 0; //value of the biggest trump in play
	char askedcolor = falls[0]->color;
	int* playable = NULL;
	int nbxcolor = 0; //number of cards of the asked color the play has

	for (int i=0;i<table[playerid-1]->hand_size;i++){
		if ((table[playerid-1]->Hand[i]->color == askedcolor) && (table[playerid-1]->Hand[i]->trump == FALSE)){
			if (nbxcolor == 0){
				playable = (int*) malloc(sizeof(int));
			} else {
				playable = (int*) realloc(playable,sizeof(int)*(nbxcolor+1));
			}
			if (playable != NULL){
				playable[nbxcolor] = i;
				(nbxcolor)=(nbxcolor)+1;
			}else{
				fprintf( stderr, "there is an error with the memory allocation for the arry of playable in the checkcard function");
				return NULL;
			}
		}
	}
	if (nbxcolor>0){ //If you have ANY card of the asked color
		return playable; // That's all you're allowed to play
	}
	/*Here you don't have any card of the asked color
	 We'll check who has the lead, 
	 If it's your mate you can play whatever you want
	 Else we'll do some more check (see below)*/
	 
	 //First let's dertermine who has the lead
	int idleader = 0; // The id of the player who has the lead
	int nbxtrump = 0; // The number of trump in hte fall
	Card** fallstrump = anytrump(falls,sizefalls,&nbxtrump);
	
	if (nbxtrump == -1){ // if there's a error with the memmory allocation inside anytrump
		return playable;
	}	
	if (nbxtrump > 0){ //if at least one trump has been found
		idleader = whowintrump(fallstrump,nbxtrump,&maxtrump); // Use the fonction with the trump order
		free(fallstrump);
		fallstrump = NULL;
	}else{
		idleader = whowin(falls,sizefalls);
	}
	if (((playerid = 1) &&(idleader = 3)) || ((playerid = 2) &&(idleader = 4)) || ((playerid = 3) &&(idleader = 1)) || ((playerid = 4) &&(idleader = 2))) {
	//your mate has the lead
		playable = (int*) malloc(sizeof(int)*(table[playerid-1]->hand_size)); //We create array of the size of the player's hand
		if (playable != NULL){ //memory error check
			for (int i= 0; i<table[playerid-1]->hand_size;i++){
				playable[i] = i; //all card are playable
			}return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the arry of playable cards in the checkcard function");
			return NULL;
		}
	}
	/*Here you don't have any card of the asked color
	 And you mate doesn't have the lead
	 We'll check if you have any trump; 
	 if no then you can play whatev
	 Else we'll see witch one you can play*/
	 
	 int nbxtrumphand = 0;
	 Card** playertrump = anytrump(table[playerid-1]->Hand,table[playerid-1]->hand_size,&nbxtrumphand); //Lets see if you have trump
	 if (nbxtrumphand == -1){ // if there's a memmory allocation error inside anytrump
	 	return NULL;
	 }else if (nbxtrumphand == 0){ //You have no trump
	 	playable = (int*) malloc(sizeof(int)*(table[playerid-1]->hand_size)); //We create array of the size of the player's hand
		if (playable != NULL){ //memory error check
			for (int i= 0; i<table[playerid-1]->hand_size;i++){
				playable[i] = i; //all card are playable
			}return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the arry of playable cards in the checkcard function");
			return NULL;
		}
	 }
	 /*Here you don't have any card of the asked color
	 And you mate doesn't have the lead
	 But you have trump 
	 Time to see which one you can play*/
	 
	if (nbxtrump == 0){ //Nobody played a trump so far
		playable = (int*) malloc(sizeof(int)*(nbxtrumphand)); //We create array of the size of the number of trump the player own
		int indexplayable =0; //To keep traock of playable index
		if (playable != NULL){ //memory error check
			for(int i=0; i<table[playerid-1]->hand_size;i++){
				if (table[playerid-1]->Hand[i]->trump == TRUE){
					playable[indexplayable] = i; //all trump are playable
					indexplayable++;
				}
			}return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the arry of playable cards in the checkcard function");
			return NULL;
		}
	}
	/*Here you don't have any card of the asked color
	 And you mate doesn't have the lead
	 But you do have trump 
	 and somebody already played a trump
	 We'll see if you can go higher or not */
	 
	 int maxtrumpinand = 0; 
	 whowintrump(playertrump,nbxtrumphand,&maxtrumpinand); // getting the value of the player's biggest trump
	 
	 if (maxtrumpinand <= maxtrump){ //You can't go higer : play anytrump
	 	playable = (int*) malloc(sizeof(int)*(nbxtrumphand)); //We create array of the size of the number of trump the player own
		int indexplayable =0; //To keep traock of playable index
		if (playable != NULL){ //memory error check
			for(int i=0; i<table[playerid-1]->hand_size;i++){
				if (table[playerid-1]->Hand[i]->trump == TRUE){
					playable[indexplayable] = i; //all trump are playable
					indexplayable++;
				}
			}return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the arry of playable cards in the checkcard function");
			return NULL;
		}
	}
	
	
	/*Just play a trump > to the biggest trump in play*/
	
	int trumporder[8] = {0,1,6,7,2,3,4,5}; // Trump order
	int indexplayable =0; //To keep track of playable index
	for (int i=0;table[playerid-1]->hand_size;i++){
		if ((table[playerid-1]->Hand[i]->trump == TRUE)&&(trumporder[table[playerid-1]->Hand[i]->value]<maxtrump)){
			if (indexplayable==0){
				playable = (int*) malloc(sizeof(int)); //We create the array 
			}else{
				playable = (int*) realloc(playable,sizeof(int)*(indexplayable+1));
			}
			if (playable != NULL){ //memory error check
				playable[indexplayable] = i;
				indexplayable++;
			}else{
				fprintf( stderr, "there is an error with the memory allocation for the arry of playable cards in the checkcard function");
				return NULL;
			}
		}
	}return playable;
}
	
	
	
Player** createplayer(){
	Player** table = (Player**) malloc(4 * sizeof(Player*));
	if (table != NULL){
		for (int i=0; i<4; i++){
			table[i] = (Player*) malloc(sizeof(Player));
			table[i]->id = i+1;
			table[i]->bet = 0;
			table[i]->hand_size = 8;
			table[i]->Hand = (Card**)malloc(sizeof(Card*)*8);
			if (table[i]->Hand != NULL){
				for(int j=0; j<8;j++) {
					table[i]->Hand[i] = NULL;
				}
			}else{
				fprintf( stderr, "there is an error with the memory allocation for the Hand array for the %d player",(i+1));
				return NULL;
			}		
		}
	}else{
		fprintf( stderr, "there is an error with the memory allocation for the array of Player");
		return NULL;
	}
	return table;
}


Card** createcards(){
	Card** deck = (Card**) malloc(32 * sizeof(Card*)); //allocating the memory
	char* color = "hcds"; // I'll iterate over it to define the color
	if (deck != NULL){
		for (int i=0; i<4; i++){  // Color's loop, each new loop mean a new color, first will be heart than club, diamond and spade
			for (int value=0; value<8;value++){ //Value's loop, each new loop mean a new card
				deck[value+8*i] = (Card*) malloc(sizeof(Card));
				deck[value+8*i]->value=value; // 7 Being the ace, 6 the 10, 5 the king.... 0 the 7
				deck[value+8*i]->color=color[i];
				deck[value+8*i]->player=0;
				deck[value+8*i]->trump=0;
				deck[value+8*i]->position= (i)*8+(value+1);
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
	Card** fallstrump = anytrump(falls,4,&nbxtrump);
	
	if (nbxtrump == -1){ // if there's a error with the memmory allocation inside anytrump
		return -1;
	}
	int player = 0;
	if (nbxtrump > 0){ //if at least one trump has been found
		int max = 0; //No real use here just a whowintrump prerequirement.
		player = whowintrump(fallstrump,nbxtrump,&max); // Use the fonction with the trump order
		free(fallstrump);
		fallstrump = NULL;
	}else{
		player = whowin(falls,4);
	}
	for (int i=0;i<4;i++){
		falls[i]->player = -player;
	}

	return player; //I'll retrun the Id of the player who won the split
}


int whowin(Card** falls,int sizefalls){
	int max = falls[0]->value;
	int indexmax = 0;
	for (int i=1 ;i<sizefalls;i++){
		if (falls[i]->color == falls[0]->color) {
			if (max<falls[i]->value){
				max = falls[i]->value;
				indexmax = i;
			}
		}
	}
	return falls[indexmax]->player;
}

int whowintrump(Card** fallstrump, int size,int* max){
	int order[8] = {0,1,6,7,2,3,4,5}; // Trump order
	int indexmax = 0;
	*max = order[fallstrump[0]->value];

	for (int i=1; i<size; i++){
		if (*max<order[fallstrump[i]->value]){
			*max = order[fallstrump[i]->value];
			indexmax = i;
		}
	}
	return fallstrump[indexmax]->player;
}

Card** anytrump(Card** falls,int sizefalls,int* nbxtrump){
	Card** fallstrump = NULL;
	for (int i = 0; i<sizefalls; i++){
		if (falls[i]->trump == 1 ){ //If so, I stock them in another array
			if (*nbxtrump == 0){
				fallstrump = (Card**) malloc(sizeof(Card*));
			} else {
				fallstrump = (Card**) realloc(fallstrump,sizeof(Card*)*(*nbxtrump+1));
			}
			if (fallstrump != NULL){
				fallstrump[*nbxtrump] = falls[i];
				(*nbxtrump)=(*nbxtrump)+1;
			}else{
				fprintf( stderr, "there is an error with the memory allocation for the trumarray in the anytrump function");
				*nbxtrump = -1;
				return NULL;
			}
		}
	}return fallstrump;
}

Boolean removecardsfromhand(Player** table,int playerid,int index){

	for (int j=index;j<table[playerid-1]->hand_size - 1;j++){ //moving everything from index to empty the last slot
		table[playerid-1]->Hand[j] = table[playerid-1]->Hand[j+1];
	}
	//decressing the hand value
	table[playerid-1]->hand_size --;
	//ajusting the Hand
	table[playerid-1]->Hand = (Card**) realloc(table[playerid-1]->Hand,(table[playerid-1]->hand_size) * sizeof(Card*));
	if (table[playerid-1]->Hand != NULL){
		return TRUE;
	}else{
		fprintf( stderr, "there is an error with the memory allocation in removecardsfromhand \n with the card at the index %d from the hand of the %d",index,playerid+1);
		return FALSE;
	}
}
	
	
