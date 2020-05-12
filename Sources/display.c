/*
 * display.c
 *
 *  Created by William Mann
 */


#include <display.h>


void magenta (int bold){
	printf("\033[%d;35m",bold);
}
void reset(){
	printf("\033[0m)");

}
void green(int bold){
	printf("\033[%d;32m",bold);
}
void yellow(int bold){
	printf("\033[%d;33m",bold);
}
void blue(int bold){
	printf("\033[%d;34m",bold);
}
void red(int bold){
	printf("\033[%d;31m",bold);
}
void cyan (int bold){
	printf("\033[%d;36m",bold);
}
