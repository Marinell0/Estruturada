#include <stdio.h>
#include <stdlib.h>

void desaloca(int **m, int linhas){
	int i;
	for(i=0; i<linhas; i++)
		free(*(m+i));
		
	free(m);
}

void leDimensoes(int *lin1, int *col1, int *col2){
	printf("\nNumero de linhas: ");
	scanf("%d", lin1);
	printf("\nNumero de colunas1: ");
	scanf("%d", col1);
	printf("\nNumero de colunas2: ");
	scanf("%d", col2);
}

int ** alocaMatriz(int lin, int col){
	int **vlin;
	int i, j, numero;
	vlin = malloc(sizeof(int*) * lin);
	for(i=0; i<lin; i++)
		*(vlin + i) = malloc (sizeof(int) * col);
		
	for(i=0; i<lin; i++){
		for(j=0; j<col; j++){
			printf("Linha %d Coluna %d: ", i, j);
			scanf("%d", &numero);
			*(*(vlin + i) + j) = numero;
		}
		printf("\n");
	}
	
	return(vlin);
}

int ** multiplicaMatrizes(int **m1, int **m2, int lin1, int col1, int col2){
	int i, j, k;
	int **r;
	
	r = alocaMatriz(lin1, col2);
	
	for(i=0; i<lin1; i++){
		for (j=0; j<col2; j++){
			r[i][j] = 0;
			for(k=0; k<col1; k++){
				r[i][j] = r[i][j] + (m1[i][k] * m2[k][j]);
			}
		}
	}
	
	return(r);
}

void imprimeMatriz(int **r, int lin1, int col2){
	int i, j;
	for(i=0; i<lin1; i++){
		for(j=0; j<col2; j++){
			printf("%d ", *(*(r+i) +j));
		}
		printf("\n");
	}
}

int main () {
	int linhas1, colunas1, colunas2;
	int ** m1;
	int ** m2;
	int ** r;

	leDimensoes(&linhas1, &colunas1, &colunas2);

	m1 = alocaMatriz(linhas1, colunas1);
	m2 = alocaMatriz(colunas1, colunas2);
	
	r = multiplicaMatrizes(m1, m2, linhas1, colunas1, colunas2);

	imprimeMatriz(r, linhas1, colunas2);

	desaloca(m1, linhas1);
	desaloca(m2, colunas1);
	desaloca(r, linhas1);

	return (0);
}

