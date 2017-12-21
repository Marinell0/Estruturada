#include <stdio.h>
#include <stdlib.h>

void main(){
	int lin, col, i, j;
	time_t t;
	srand((unsigned) time(&t));
	
	printf("Numero de linhas da matriz: ");
	scanf("%d", &lin);
	printf("Numero de colunas da matriz: ");
	scanf("%d", &col);
	
	printf("\n-----------------------------MATRIZ A-----------------------------------\n\n");	
	int A[lin][col];
	for(i=0; i<lin; i++){
		for(j=0; j<col; j++){
			A[i][j]=rand() %9+1;
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
	
	int tam=(lin*col), aux=0;
	printf("\n\n");
	if(lin%2 && col%2){
		tam--;
	}
	
	while(tam){
		for(i=aux; i<(col-1)-aux; i++){
			printf("%d ", A[aux][i]);
			tam--;
		}
		for(i=aux; i<(lin-1)-aux; i++){
			printf("%d ", A[i][(col-1)-aux]);
			tam--;
		}
		for(i=(col-1)-aux; i>aux; i--){
			printf("%d ", A[(lin-1)-aux][i]);
			tam--;
		}
		for(i=(lin-1)-aux; i>aux; i--){
			printf("%d ", A[i][aux]);
			tam--;
		}
		aux++;
	}
	if(lin%2 && col%2){
		printf("%d ", A[lin/2][col/2]);
	}
}	
