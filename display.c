/*This librarry will regroup every fonction that display something
 * to the user*/
#include <stdio.h>
#include <stdlib.h>


/*This series of protocol just set the output color */

void magenta (int bold){
	printf("\033[%d;35m",bold);
	printf("hello\n");
}
void reset(){
	printf("\033[0m)");

}
void green(int bold){
	printf("\033[%d;32m",bold);
	printf("hello\n");
}
void yellow(int bold){
	printf("\033[%d;33m",bold);
	printf("hello\n");
}
void blue(int bold){
	printf("\033[%d;34m",bold);
	printf("hello\n");
}
void red(int bold){
	printf("\033[%d;31m",bold);
	printf("hello\n");
}
void cyan (int bold){
	printf("\033[%d;36m",bold);
	printf("hello\n");
}



int welcome();
int main(){
	magenta(0);
	magenta(1);
	red(0);
	red(1);
	yellow(0);
	yellow(1);
	blue(0);
	blue(1);
	green(0);
	green(1);
	return EXIT_SUCCESS;
}
