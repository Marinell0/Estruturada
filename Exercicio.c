/*
Escreva uma função que receba um vetor de numeros reais e tenha como valor de retorno um novo vetor, alocado dinamicamente, com os elementos do vetor original em ordem reversa. A função deve ter como valor de retorno o ponteiro do vetor alocado, seguindo o prototipo.

	Float * reverso(int m, float *v);
	
Faça uma função main para testar a sua função. Na main não se esqueça de liberar a memoria alocada pela função reverso.
*/

/*
Escreva uma função que receba um vetor de inteiros e tenha como valor de retorno um novo vetor, alocado dinamicamente, apenas com os elementos pares do vetor original. A função deve ter como valor de retorno o ponteiro do vetor alocado e preencher o endeço de memória passado com a dimensão do novo vetor, seguindo o protótipo;

	int * somente_pares (int n, int * v, int * npares);
	
Faça uma função main para testar a sua função. Na função main, não se esqueça de liberar a memória alocada pela função auxiliar.
*/

#include <stdio.h>
#include <stdlib.h>

int i;

float * reverso(int m, float * v){

	float * v2;
	v2 = malloc(m * sizeof(float));
	
	for(i=0; i<m; i++){
		v2[i] = v[(m-1)-i];
	}
	
	return(v2);
}

void main(){
	int tam;

	system("clear");
	printf("Qual o tamanho do seu vetor: ");
	scanf("%d", &tam);
	
	float a[tam];
	
	for(i=0; i<tam; i++){
		printf("Valor do numero %d: ", i);
		scanf("%f", &a[i]);
	}
	printf("\n\n===================== Vetor original ===================== \n\n");
	
	for(i=0; i<tam; i++)
		printf("%.0f ", a[i]);
		
		
	float * reverse = reverso(tam, a);
	
	printf("\n\n===================== Vetor reverso ===================== \n\n");
	
	for(i=0; i<tam; i++)
		printf("%.0f ", reverse[i]);
		
	printf("\n\n");
	
	free(reverse);

}	
