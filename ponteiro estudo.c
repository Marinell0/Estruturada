#include <stdio.h>
#include <stdlib.h>

int soma(int *a, int *b){
	
	*a = 13;
	*b = 57;
	
	return(*a + *b);
}

void main(){
	int a, b, c;
	int *pa;
	int *pb;
	
	pa = &a;
	pb = &b;
	
	a = 10;
	b = 5;
	
	int **ppa;
	ppa = &pa;
	
	printf("%d ", *pa);
	
	*ppa = pb;
	
	printf("%d ", *pa);
	
	printf("\na + b = %d\n", soma(pa,pb));
	
	printf("a = %d, b = %d", a, b);
}
