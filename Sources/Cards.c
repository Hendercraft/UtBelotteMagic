#include <Cards.h>


int turn(Player** table,Bet gamebet,char* playname,int playerid,int* ItstheTHcard){

	/****************************************************/
	/***************VARIABLES DECLARATION***************/
	/**************************************************/
	int realplayerid[8] = {0,1,2,3,4,1,2,3}; // Cheap trick that avoid writing some IF statements.
	Card** falls = (Card**)malloc(sizeof(Card*)); //Where the player will play their cards.
	falls[0] = NULL;
	int *playableCards; // An array that will contain the index of playable cards.
	int sizefalls = 0; // The "pseudo" size of the falls, it's the number of card played so far.
	int chosenCard; // Card chosen by the player.
	int numberOfPlayables = 0; // The number of cards a given player can play.
	Boolean gooduserinput = FALSE; // Did the user give a playable card?

	/*Filling the Falls*/
	for (int nbxcardsplayed=0; nbxcardsplayed<4; nbxcardsplayed++){
		int currentplayer = realplayerid[playerid+nbxcardsplayed];
		clrscr(); // Dealing with the interface.
		ingameMenu(gamebet,playname,table, falls,sizefalls);

		// Getting the player's playable card
		playableCards = checkcard(table,falls,currentplayer,sizefalls,&numberOfPlayables);
		if (currentplayer == 1){
			do {
				chosenCard = verify(1,table[0]->hand_size); // This will return a value between 1 and hand_size.
				chosenCard--;	// We have to apply an offset.
					for(int j=0;j<numberOfPlayables;j++){
						if(chosenCard == playableCards[j]){
							gooduserinput = TRUE;
						}
					}
			}while (gooduserinput == FALSE);
		}else{
			chosenCard = IAcompute(table,falls,currentplayer,sizefalls,playableCards,numberOfPlayables); //asking the AI for a card.
		}
		falls = playcard(table,falls,currentplayer,chosenCard,&sizefalls,ItstheTHcard);
		removecardsfromhand(table,currentplayer,chosenCard);
		if(falls == NULL){
			fprintf( stderr, "there is an error with the memory allocation inside playcard");
			fprintf( stderr, "this was while playing the %dth card",*ItstheTHcard);
			return -1;
		}
	}

	int winner = Endofturn(falls); // Getting the winner.
	free(falls);
	falls = NULL;
	return winner;

}



void cardsdeal(Player** table,Card** deck,int dealerid){

	int whosecard[7] = {0,1,2,3,0,1,2}; // Cheap trick that avoid  writing some IF statements.
	int iterable1=0, iterable2=0, iterable3=0 ,iterable4 = 0;


	for (int i=0;i<32;i++){  // Goes through the whole deck to deal it to players.

		if ((deck[i]->position <=3) || (deck[i]->position >=13 && deck[i]->position <=14) || (deck[i]->position >=21 && deck[i]->position <=23)){ // Cards of the player at the left of the dealer.
			table[whosecard[dealerid]]->Hand[iterable1] = deck[i];
			deck[i]->player = whosecard[dealerid] + 1;
			iterable1++;

		}else if ((deck[i]->position >=4 && deck[i]->position <=6) || (deck[i]->position >=15 && deck[i]->position <=16) || (deck[i]->position >=24 && deck[i]->position <=26)){ // Cards of the player in front of the dealer.

			table[whosecard[dealerid+1]]->Hand[iterable2] = deck[i];
			deck[i]->player = whosecard[dealerid+1] + 1;
			iterable2++;


		} else if ((deck[i]->position >=7 && deck[i]->position <=9) || (deck[i]->position >=17 && deck[i]->position <=18) || (deck[i]->position >=27 && deck[i]->position <=29)){ // Cards of the player on the left of the dealer.

			table[whosecard[dealerid+2]]->Hand[iterable3] = deck[i];
			deck[i]->player = whosecard[dealerid+2] + 1;
			iterable3++;

		}else{ // Cards of the player who is currently dealing.

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
		} else if ('n' == trump){
		    deck[i]->trump = FALSE;
		} else {
            deck[i]->trump = TRUE;
		}
	}
	return;
}


int* checkcard(Player** table,Card** falls,int playerid,int sizefalls,int* outputsize){
/*This function is definitely one of the hardest to read
 I'm pretty sure there's way to improve it by a lot
 but for now we'll stick with it because it works*/




	int max = 0 ; // No real use here, it's just a prerequisite of whowin.
	int maxtrump = 0; // Value of the biggest trump in play.
	int* playable = NULL;
	int nbxcolor = 0; // Number of cards of the asked color the player has.

	/**You're the first one to play**/
	/*You can play whatever you want*/
	if(falls[0] == NULL){
		playable = (int*) malloc(sizeof(int) * (table[playerid-1]->hand_size));
		if (playable != NULL){
			for (int i=0;i<table[playerid-1]->hand_size;i++){
				playable[i] = i;
			}
			*outputsize = table[playerid-1]->hand_size;
			return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the array of playable cards in the checkcard function");
				return NULL;
		}
	}
	char askedcolor = falls[0]->color;
	/*Let's check if you have any card of the asked color (If it's not a trump)*/
	/*If so, we'll count them*/

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
				fprintf( stderr, "there is an error with the memory allocation for the array of playable cards in the checkcard function");
				return NULL;
			}
		}
	}
	if (nbxcolor>0){ // If you have ANY card of the asked color.
		*outputsize = nbxcolor;
		return playable; // That's all you're allowed to play.
	}



	/*Here you don't have any card of the asked color*/
	/**********We'll check who has the lead **********/

	/*If your mate has the lead you can play whatever you want*/
	/********Else we'll do some more check (see below)********/

	 // First let's determine who has the lead.
	int idleader = 0; // The ID of the player who has the lead.
	int nbxtrump = 0; // The number of trumps in the fall.
	Card** fallstrump = anytrump(falls,sizefalls,&nbxtrump);

	if (nbxtrump == -1){ // if there's a error with the memory allocation inside anytrump.
		return playable; // It's NULL.
	}
	if (nbxtrump > 0){ // If at least one trump has been found.
		idleader = whowintrump(fallstrump,nbxtrump,&maxtrump); // Use the function with the trump order.
		free(fallstrump);
		fallstrump = NULL;
	}else{
		idleader = whowin(falls,sizefalls,&max);
	}
	if (((playerid == 1) &&(idleader == 3)) || ((playerid == 2) &&(idleader == 4)) || ((playerid == 3) &&(idleader == 1)) || ((playerid == 4) &&(idleader == 2))) {
	// If your mate has the lead
		playable = (int*) malloc(sizeof(int)*(table[playerid-1]->hand_size)); // We create an array of the size of the player's hand.
		if (playable != NULL){ // Memory error check
			for (int i= 0; i<table[playerid-1]->hand_size;i++){
				playable[i] = i; // All cards are playable
			}
			*outputsize = table[playerid-1]->hand_size;
			return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the array of playable cards in the checkcard function");
			return NULL;
		}
	}
	/*Here you don't have any card of the asked color
	 And you mate doesn't have the lead
	 We'll check if you have any trumps;
	 if not then you can play whatever
	 Else we'll see which one you can play*/

	 int nbxtrumphand = 0;
	 Card** playertrump = anytrump(table[playerid-1]->Hand,table[playerid-1]->hand_size,&nbxtrumphand); //Lets see if you have trumps.
	 if (nbxtrumphand == -1){ // If there's a memory allocation error inside anytrump.
	 	return NULL;
	 }else if (nbxtrumphand == 0){ //You have no trump
	 	playable = (int*) malloc(sizeof(int)*(table[playerid-1]->hand_size)); // We create array of the size of the player's hand.
		if (playable != NULL){ // Memory error check
			for (int i= 0; i<table[playerid-1]->hand_size;i++){
				playable[i] = i; // All cards are playable
			}
			*outputsize = table[playerid-1]->hand_size;
			return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the array of playable cards in the checkcard function");
			return NULL;
		}
	 }
	 /*Here you don't have any card of the asked color
	 And your mate doesn't have the lead
	 But you have trump
	 Time to see which one you can play*/

	if (nbxtrump == 0){ // Nobody played a trump so far
		playable = (int*) malloc(sizeof(int)*(nbxtrumphand)); // We create array of the size of the number of trump the player own.
		int indexplayable =0; // To keep traock of playable index.
		if (playable != NULL){ // Memory error check.
			for(int i=0; i<table[playerid-1]->hand_size;i++){
				if (table[playerid-1]->Hand[i]->trump == TRUE){
					playable[indexplayable] = i; //all trumsp are playable.
					indexplayable++;
				}
			}
			*outputsize = nbxtrumphand;
			return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the array of playable cards in the checkcard function");
			return NULL;
		}
	}
	/*Here you don't have any card of the asked color
	 And you mate doesn't have the lead
	 But you do have a trump
	 and somebody has already played a trump
	 We'll see if you can go higher or not */

	 int maxtrumpinhand = 0;
	 whowintrump(playertrump,nbxtrumphand,&maxtrumpinhand); // Getting the value of the player's biggest trump.

	 if (maxtrumpinhand <= maxtrump){ // You can't go higher: play anytrump
	 	playable = (int*) malloc(sizeof(int)*(nbxtrumphand)); // We create an array of the size of the number of trumps the player owns.
		int indexplayable =0; // To keep track of playable index.
		if (playable != NULL){ // Memory error check
			for(int i=0; i<table[playerid-1]->hand_size;i++){
				if (table[playerid-1]->Hand[i]->trump == TRUE){
					playable[indexplayable] = i; // All trumps are playable.
					indexplayable++;
				}
			}
			*outputsize = nbxtrumphand;
			return playable;
		}else{
			fprintf( stderr, "there is an error with the memory allocation for the arry of playable cards in the checkcard function");
			return NULL;
		}
	}


	/*Just play a trump > to the biggest trump in play*/

	int trumporder[8] = {0,1,6,7,2,3,4,5}; // Trump order
	int indexplayable =0; // To keep track of playable index
	for (int i=0;i<table[playerid-1]->hand_size;i++){
		if ((table[playerid-1]->Hand[i]->trump == TRUE)&&(trumporder[table[playerid-1]->Hand[i]->value]>maxtrump)){
		// The trump is bigger than the biggest one in fall
		// So its index is added to playable
			if (indexplayable==0){
				playable = (int*) malloc(sizeof(int)); //We create the array
			}else{
				playable = (int*) realloc(playable,sizeof(int)*(indexplayable+1));
			}
			if (playable != NULL){ // Memory error check
				playable[indexplayable] = i;
				indexplayable++;
			}else{
				fprintf( stderr, "there is an error with the memory allocation for the arry of playable cards in the checkcard function");
				return NULL;
			}
		}
	}
	*outputsize = indexplayable; // Playable is the size of maximun index + 1
	return playable;
}

int IAcompute(Player** table, Card** falls,int playerid,int sizefalls,int* allowedcard,int sizeallowedcard){

	/****************************************************/
	/***************VARIABLES DECLARATION***************/
	/**************************************************/

	int nbxcolor = 0; // The number of cards of the asked color that are playable.
	int nbxtrump = 0; // The number of trumps that are playable.
	int maxhand = 0; // The value of the biggest card in hand.
	int maxfalls= 0; // The value of the biggest card in play.
	Card** playablecard = malloc(sizeof(Card*)* sizeallowedcard);
	if (playablecard == NULL){ // Checking if the malloc didn't return NULL.
		fprintf( stderr, "there is an error with the memory allocation for the arry of playable cards in the IAcompute function");
		return -1;
	}
	for(int i=0;i<sizeallowedcard;i++){ // Filling the array with the pointer of playable Card
		playablecard[i] = table[playerid-1]->Hand[allowedcard[i]];
	}

	/**First we'll check if the AI is the first to play**/
	/**If so, we'll play the card with the lowest value*/
	/***********IT PRIORITISE NO TRUMP FIRST***********/

	if (falls[0]==NULL){

        // Checking if the have an hand full of trump.
        for (int i = 0;i<sizeallowedcard;i++){
            if(table[playerid-1]->Hand[allowedcard[i]]->trump == TRUE){
			nbxtrump++; // Whenever we can play a trump, we increment this counter.
            }
        }


		if (nbxtrump == sizeallowedcard){ // We have only trump in hand in THIS SPECIFIC case.
			int returnindex = mintrump(playablecard,sizeallowedcard,-1);
			free(playablecard);
			playablecard = NULL;
			return (returnindex); // Play the lowest trump
		}else{ // 1st and 3rd case
			int returnindex = mincard(playablecard,sizeallowedcard,-1);
			free(playablecard);
			playablecard = NULL;
			return (returnindex); // Play the lowest card in hand
		}
	}

    /***************We can have  3 case here************/
	/***********1st-We need to play the color**********/
	/***********2nd-We need to play a trump***********/
	/********3rd-We can play whatever we like********/

	/****************************************************/
	/********First we'll see in wich one we are*********/
	/**************************************************/


	for (int i = 0;i<sizeallowedcard;i++){
		if ((table[playerid-1]->Hand[allowedcard[i]]->color == falls[0]->color) && table[playerid-1]->Hand[allowedcard[i]]->trump == FALSE){
			nbxcolor++; //Whenever we can play a card of the asked color, we increment this counter
		}else if(table[playerid-1]->Hand[allowedcard[i]]->trump == TRUE){
			nbxtrump++; //Whenever we can play a trump, we increment this counter
		}
	}

	
	if (nbxcolor == sizeallowedcard){ // 1st case

		whowin(playablecard,sizeallowedcard,&maxhand); // Computing the maximum of our playable Cards.
		whowin(falls,sizefalls,&maxfalls); // Computing the maximum of the fall.

		if (maxhand < maxfalls) { //If the AI can't win.
			maxfalls = -1; //This way mincard will return the index of the lowest card in hand with no threshold.
		}
		int returnindex = mincard(playablecard,sizeallowedcard,maxfalls);
		free(playablecard);
		playablecard = NULL;
		return returnindex;

	}else if(nbxtrump == sizeallowedcard){ // 2nd case
		whowintrump(playablecard,sizeallowedcard,&maxhand); // Computing the max of our playable Cards.
		whowintrump(falls,sizefalls,&maxfalls); // Computing the max of the fall.

		if (maxhand < maxfalls) { // If the AI can't win.
			maxfalls = -1; //This way mincard will return the index of the lowest card in hand with no threshold
		}
		int returnindex = mintrump(playablecard,sizeallowedcard,maxfalls);
		free(playablecard);
		playablecard = NULL;
		return allowedcard[returnindex];
	}else{ //3rd
		int returnindex = mincard(playablecard,sizeallowedcard,-1);
		free(playablecard);
		playablecard = NULL;
		return allowedcard[returnindex];
	}
}









Player** createplayer(){
	Player** table = (Player**) malloc(4 * sizeof(Player*));
	if (table != NULL){
		for (int i=0; i<4; i++){
			table[i] = (Player*) malloc(sizeof(Player));
			table[i]->id = i+1;
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
	Card** deck = (Card**) malloc(32 * sizeof(Card*)); // Allocating the memory
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
	int max = 0; // No real use here just a whowintrump and whowin requirement.
	Card** fallstrump = anytrump(falls,4,&nbxtrump);

	if (nbxtrump == -1){ // if there's a error with the memory allocation inside anytrump.
		return -1;
	}
	int player = 0;
	if (nbxtrump > 0){ // if at least one trump has been found.
		player = whowintrump(fallstrump,nbxtrump,&max); // Use the fonction with the trump order.
		free(fallstrump);
		fallstrump = NULL;
	}else{
		player = whowin(falls,4,&max);
	}
	for (int i=0;i<4;i++){
		falls[i]->player = -player;
	}

	return player; // I'll return the Id of the player who has won the split.
}


int whowin(Card** falls,int sizefalls,int* max){
	*max = falls[0]->value;
	int indexmax = 0;
	for (int i=1 ;i<sizefalls;i++){
		if (falls[i]->color == falls[0]->color) {
			if (*max<falls[i]->value){
				*max = falls[i]->value;
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
				fprintf( stderr, "there is an error with the memory allocation for the trumparray in the anytrump function");
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
	// Decressing the hand value
	table[playerid-1]->hand_size --;
	// Ajusting the Hand
	table[playerid-1]->Hand = (Card**) realloc(table[playerid-1]->Hand,(table[playerid-1]->hand_size) * sizeof(Card*));
	if (table[playerid-1]->Hand != NULL || index == 0){
		return TRUE;
	}else {
		fprintf( stderr, "there is an error with the memory allocation in removecardsfromhand \n with the card at the index %d from the hand of the %d",index,playerid+1);
		return FALSE;
	}
}


Card** playcard(Player** table,Card** falls,int playerid,int cardid,int* sizefalls,int* newposition){
	falls = (Card**) realloc(falls,sizeof(Card*) * (*sizefalls+1));
	if (falls != NULL){ //If the allocation id done correctly
		falls[*sizefalls] = table[playerid-1]->Hand[cardid]; //copy the pointer to the falls
        falls[*sizefalls]->position = *newposition; //Changing the position of the card for the future deck
		*newposition = *newposition+1;
		*sizefalls= *sizefalls+1; //change sizefall
		return falls;
	}else{
		fprintf(stderr,"there is an error with the memory allocation in playcard (curent falls size : %d)\n",*sizefalls);
		fprintf(stderr,"when player %d plays the card at the %d index of his hand",playerid,cardid);
		return NULL;
	}
}

int mincard(Card** cardarray,int size,int supp){
	int min = 9;
	int indexmin = 0;
	for (int i=0;i<size;i++){
		if ((cardarray[i]->trump == FALSE) && (cardarray[i]->value < min) && (cardarray[i]->value > supp)){
			indexmin = i;
			min = cardarray[i]->value;
		}
	}return indexmin;
}

int mintrump(Card** cardarray,int size,int supp){
	int trumporder[8] = {0,1,6,7,2,3,4,5}; // Trump order
	int min = 9;
	int indexmin = 0;
	for (int i=0;i<size;i++){
		if ((cardarray[i]->trump == TRUE) && (trumporder[cardarray[i]->value] < min) && (trumporder[cardarray[i]->value] > supp)){
			indexmin = i;
			min = trumporder[cardarray[i]->value];
		}
	}return indexmin;
}

void shuffle(Card** deck,int cutfrom){
	if (cutfrom==-1){
		for(int i =0; i<5;i++){
			shuffle(deck,rand() % 32);
		}
	}return;
	int newposition = 1;
	for (int i = cutfrom;i<32;i++){
		deck[i]->position = newposition;
		newposition++;
	}
	for(int i = newposition; newposition<33; newposition++){
		deck[i]->position = newposition;
		newposition++;
	}return;
}
