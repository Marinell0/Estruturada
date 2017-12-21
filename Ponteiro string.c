#include <stdio.h>
#include <stdlib.h>

void main(){
	char *c;
	c = malloc (100*sizeof(char));
	scanf("%s", c); //string quer receber um endereço, e por isso n pode colocar *c, pois cairia em conteúdo.
	printf("\n%s\n", c);
}
