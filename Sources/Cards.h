#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    FALSE = 0,
    TRUE = 1
}Boolean;

typedef struct Card {
    char value;
    char color;
    int player;
    Boolean trump;
}Card;

/*This fonction generate and retrun a array of Cards,already
 set to their value*/
Card* creatcards();

