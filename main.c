#include <stdlib.h>
#include "myMalloc.h"
#include <stdio.h>
#include <string.h>

#define malloc( x ) myMalloc( x , __FILE__, __LINE__)
#define free( x ) myFree( x , __FILE__, __LINE__)
#define calloc( y , x ) myCalloc( y , x , __FILE__, __LINE__) 
int main(){

//	char *what = (char *)calloc(5, 100);
//	free(what);
	char *help = (char *)malloc(1000);
	free(help);
	int x;
	free(&x);
	atexit((void *)&LeakDetect);
	return 0;
}
