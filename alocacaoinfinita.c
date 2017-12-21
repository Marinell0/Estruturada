#include <stdio.h>
#include <stdlib.h>

void main(){
	int i;
	for(i=0;;i++){
		malloc(sizeof(double));
		if(!(i%100000))
			printf("%d\t", i);
	}
}
