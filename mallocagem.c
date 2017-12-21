#include <stdio.h>
#include <stdlib.h>

void main(){
	double *v;
	int i;
	
	for (i=0; i<100000; i++){
		v = malloc(10000 * sizeof(double));
	}
	getchar();
}
	
