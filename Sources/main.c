/*
 * main.c
 *
 *  Created by William Mann
 */

#include <highscore.h>
#include <menu.h>

typedef enum {
    FALSE = 0
    TRUE = 1
}Boolean

typedef struct {
    char value
    char* color
    int player
    Boolean trump
{Cards

int main(){

    int operation, play=0;

    while(play==0){

        clrscr();
        menuVisual();

            operation = verify(3);
            if(operation == 1){
                clrscr();
                printf("Launching game...");
                play=1;

            } else if(operation == 2){
                clrscr();
                printf("Showing highscores...");
                scoreVisual();
                operation = verify(3);
                if(operation==2){
                    return EXIT_SUCCESS;
                }

            } else if(operation == 3){
                return EXIT_SUCCESS;
            }


    }

    return EXIT_SUCCESS;

}
