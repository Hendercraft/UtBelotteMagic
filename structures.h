#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED


/* Creation of structure composed of: */
typedef struct {
	int contract; /*an integer for the chosen contract. 1 is N points, 2 capot, 3 generale, 4 coinche and 5 surcoinche. 0 is no contract*/
	int points; /*an integer for the points that the contract gives*/
	char trump; /*a character for the color of the trump + t for all trump and n for no trump*/
	int coinche; //0 if nothing, 1 for coinche, 2 for surcoinche
	int team; //  1 for team player and 2 for team enemy
} Bet;


/* Creation of structure composed of: */
typedef struct {
	int victories; /*an integer for the number of victories*/
	int loses; /*an integer for the number of loses*/
	char name[15]; /*a string for the name of the player*/
} highscore;




/* Boolean type definition */
typedef enum {
 FALSE = 0,
 TRUE = 1
} Boolean;


/* Card type definition */
typedef struct {
    int value; //Card value,between 0 and 7
    char color; // Either c for clubs h for heart .......
    int player; // The owner of the card, 0 means unowned , 1 to 4 is the played id
    //It can be also set to -1 or -2, if the card has been played and won either by one team or the other
    Boolean trump; //Is the card a trump ?
    int position; // Its position in the deck
} Card;


/* Player type definition */
typedef struct{
	Card** Hand; //Dynamic array of cards representing the cards in hands
	int id; //player id, 0 is player, 2 is West...
	int hand_size; //Number of cards in hand
} Player;


#endif // STRUCTURES_H_INCLUDED
