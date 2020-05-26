#include <Cards.h>

Card* creatcards(){
	Card* deck = (Cards*) malloc(32 * sizeof(Cards)); //allocating the memory
	char* color = "hcds" // I'll itertate over it to define the color
	if (deck != NULL){
		for (int i=0; i<4; i++){
			for (int value=0; value<8;value++){
			
				deck[value+8*i].value=value;
				deck[value+8*i].color=color[i];
				deck[value+8*i].player=-1;
				deck[value+8*i].trump=0;
			}
		}
		return deck;
	}
	else {
		fprintf( stderr, "there is an error with the memory allocation for the array of Cards");
		return NULL
	}



Card* WhoWins(Card* falls){
	int* trump,
	int j=0;
	for (int = i; i<4;i++){
		if falls[i].trump=1
			trump[j]=i;
			j++;
		}
	}
			
		
