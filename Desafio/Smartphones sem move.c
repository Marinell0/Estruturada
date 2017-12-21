/*
Autores: Gabriel Marinello Moura Leite .......... 2016.1.08.028
		 Eduardo Alberto de Paula Carvalho ...... 2016.1.08.027
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct posicao{
	int x;
	int y;
	int largura;
	int altura;
};

//#######################################################################################################################

int contemTela(int posatual, struct posicao *posicoes, int x, int y){
	
	
	if(x >= posicoes[posatual].x && x <= (posicoes[posatual].x + posicoes[posatual].largura) && y >= posicoes[posatual].y && y <= (posicoes[posatual].y + posicoes[posatual].altura)){
		return(1);
	}
	return(0);
}

//#######################################################################################################################

void abre(FILE *entrada, FILE *saida, int *atual, int xmax, int ymax, struct posicao *posicoes, int pcomando){
	int x, y, largura, altura;
	int negado=0, i;
	
	fscanf(entrada, "%d %d %d %d", &x, &y, &largura, &altura);
	
	if(x < 0 || y < 0 || (x + largura) > xmax || (y + altura) > ymax){
		return;
	}
	
	//------------------------ FOR PARA VER SE HÁ UMA TELA DENTRO DA OUTRA --------------------------------------------------
	
	for(i=0; i<*atual; i++){
		if(((posicoes[i].x <= x && x <= (posicoes[i].x + posicoes[i].largura)) && (posicoes[i].y <= y && y <= (posicoes[i].y + posicoes[i].altura))) || 
		((x <= posicoes[i].x && (posicoes[i].x + posicoes[i].largura) <= (x + largura)) && (y <= posicoes[i].y && (posicoes[i].y + posicoes[i].altura)) <= (y + altura))){ 
			negado=1;
			break;
		}
	}
	
	//-------------------------- FOR PARA VER SE AS PONTAS NÃO ENTRAM DENTRO DE OUTRA TELA ----------------------------------
	
	for(i=0; i<*atual; i++){
		if((x + largura) >= posicoes[i].x && (x + largura) <= (posicoes[i].x + posicoes[i].largura) && y >= posicoes[i].y && y <= (posicoes[i].y + posicoes[i].altura) ||
		(x >= posicoes[i].x && x <= (posicoes[i].x + posicoes[i].largura) && y >= posicoes[i].y && y <= (posicoes[i].y + posicoes[i].altura)) ||
		((y + altura) >= posicoes[i].y && (y + altura) <= (posicoes[i].y + posicoes[i].largura) && x >= posicoes[i].x && x <= (posicoes[i].x + largura))){
			negado=1;
			break;
		}
	}

	//----------------------------- FOR PARA VER SE UMA TELA NÃO FICA POR CIMA DA OUTRA, SEM ESTAR DENTRO -------------------
	
	for(i=0; i<*atual; i++){
		if((x >= posicoes[i].x && (x + largura) <= (posicoes[i].x + posicoes[i].largura)) && (y <= posicoes[i].y &&  (y + altura) >= (posicoes[i].y + posicoes[i].altura)) ||
		(y >= posicoes[i].y && (y + altura) <= (posicoes[i].y + posicoes[i].altura)) && (x <= posicoes[i].x && (x + largura) >= (posicoes[i].x + posicoes[i].largura))){
			negado=1;
			break;
		}
	}
	
	//-----------------------------------------------------------------------------------------------------------------------
	
	if(negado){
		printf("Comando %d: ABRE - janela nao cabe\n", pcomando);
		fprintf(saida, "Comando %d: ABRE - janela nao cabe\n", pcomando);
	}else{
		posicoes[*atual].x = x;
		posicoes[*atual].y = y;
		posicoes[*atual].largura = largura;
		posicoes[*atual].altura = altura;
		++*atual;	
	}	
	
}

//#######################################################################################################################

void fecha(FILE *entrada, FILE *saida, int *atual, int xmax, int ymax, struct posicao *posicoes, int pcomando){
	int i, j, x, y, existetela=0;
	
	fscanf(entrada, "%d %d", &x, &y);
	
	for(i=0; i<*atual; i++){
		if(contemTela(i, posicoes, x, y)){
			existetela = 1;
			for(j=i; j<(*atual-1); j++){
				posicoes[j].x = posicoes[j+1].x;
				posicoes[j].y = posicoes[j+1].y;
				posicoes[j].largura = posicoes[j+1].largura;
				posicoes[j].altura = posicoes[j+1].altura;
			}
		}
	}
	
	if(existetela){
		--*atual;
	}else{
		printf("Comando %d: FECHA - nao ha janela na posicao\n", pcomando);
		fprintf(saida, "Comando %d: FECHA - nao ha janela na posicao\n", pcomando);
	}
}

//#######################################################################################################################

void redimensiona(FILE *entrada, FILE *saida, int *atual, int xmax, int ymax, struct posicao *posicoes, int pcomando){
	int x, y, largura, altura, i, negado=0, temtela=0;
	
	
	fscanf(entrada, "%d %d %d %d", &x, &y, &largura, &altura);
	
	for(i=0; i<*atual; i++){
		if((contemTela(i, posicoes, x, y))){
			temtela=i;
			break;
		}
	}
	
	if(temtela != i){
		printf("Comando %d: REDIMENSIONA - nao ha janela na posicao\n", pcomando);
		fprintf(saida, "Comando %d: REDIMENSIONA - nao ha janela na posicao\n", pcomando);
		
		return;
	}
	
	if((x + largura) > xmax || (y + altura) > ymax){
		printf("Comando %d: REDIMENSIONA - janela nao cabe\n", pcomando);
		fprintf(saida, "Comando %d: REDIMENSIONA - janela nao cabe\n", pcomando);
		return;
	}
	
	//----------------------------------------- FOR PARA TESTAR SE AS PONTAS ENTRAM EM OUTRA TELA ---------------------------
	
	for(i=0; i<*atual; i++){
		if (i == temtela){
			if(i == (*atual - 1)) break;
			i++;
		}
		
		if((posicoes[temtela].x + largura) >= posicoes[i].x && (posicoes[temtela].x + largura) <= (posicoes[i].x + posicoes[i].largura) && posicoes[temtela].y >= posicoes[i].y && posicoes[temtela].y <= (posicoes[i].y + posicoes[i].altura) || 
		((posicoes[temtela].y + altura) >= posicoes[i].y && (posicoes[temtela].y + altura) <= (posicoes[i].y + posicoes[i].largura) && posicoes[temtela].x >= posicoes[i].x && posicoes[temtela].x <= (posicoes[i].x + posicoes[i].largura)) ||
		(posicoes[temtela].x + largura) >= posicoes[i].x && (posicoes[temtela].x + largura) <= (posicoes[i].x + posicoes[i].largura) && posicoes[temtela].y > posicoes[i].y && posicoes[temtela].y < (posicoes[i].y + posicoes[i].altura)){
			negado=1;
			break;
		}
	}
	
	//-----------------------------------------------------------------------------------------------------------------------
	
	for(i=0; i<=*atual; i++){
		if((posicoes[temtela].x >= posicoes[i].x && (posicoes[temtela].x + largura) <= (posicoes[i].x + posicoes[i].largura)) && (posicoes[temtela].y <= posicoes[i].y &&  (posicoes[temtela].y + altura) >= (posicoes[i].y + posicoes[i].altura)) ||
		(posicoes[temtela].y >= posicoes[i].y && (posicoes[temtela].y + altura) <= (posicoes[i].y + posicoes[i].altura)) && (posicoes[temtela].x <= posicoes[i].x && (posicoes[temtela].x + largura) >= (posicoes[i].x + posicoes[i].largura))){
			negado=1;
			
			break;
		}
	}
	
	if(negado){
		printf("Comando %d: REDIMENSIONA - janela nao cabe\n", pcomando);
		fprintf(saida, "Comando %d: REDIMENSIONA - janela nao cabe\n", pcomando);
	}else{
		posicoes[temtela].largura = largura;
		posicoes[temtela].altura = altura;
				
	}
	
}

//#######################################################################################################################

void move(int x, int y, int dx, int dy, int *posatual, int *dxerro, int *dyerro, struct posicao *posicoes, int xmax, int ymax, int *parede){

	int i, aba;
	int horizontal = dx;
	int vertical = dy;
	int temtela = 0;
	
	for(i=0; i<*posatual; i++){
		if(contemTela(i, posicoes, x, y)){
			aba=i;
			break;
		}
	}

	if(*dxerro != 0){
		dx = dx - *dxerro;
		horizontal = dx;
	}
	
	
	if(*dyerro != 0){
		dy = dy - *dyerro;
		vertical = dy;
	}
	
	for(dx=dx, dy=dy; dx>0 || dy>0 ; dx--, dy--){
		if(dx <= 0) dx = 0;
		if(dy <= 0) dy = 0;
		if(dx != 0) posicoes[aba].x++;
		if(dy != 0) posicoes[aba].y++;
		
		if(posicoes[aba].x <= 0 || posicoes[aba].y <= 0 || (posicoes[aba].x + posicoes[aba].largura) >= xmax || (posicoes[aba].y + posicoes[aba].altura) >= ymax){
			if(dx != 0) posicoes[aba].x--;
			if(dy != 0)	posicoes[aba].y--;
			*dxerro = dx;
			*dyerro = dy;
			dx = 0;
			dy = 0;
			*parede=1;
			return;
		}
		
		for(i=0; i<(*posatual-1); i++){
			if(i == aba) i++;
			if(i > *posatual) break;
			
			if(posicoes[aba].x >= posicoes[i].x && posicoes[aba].x <= (posicoes[i].x + posicoes[i].largura) && posicoes[aba].y >= posicoes[i].y && posicoes[aba].y <= (posicoes[i].y + posicoes[aba].altura) ||
			(posicoes[aba].x >= posicoes[i].x && posicoes[aba].x <= (posicoes[i].x + posicoes[i].largura) && posicoes[aba].y >= posicoes[i].y && posicoes[aba].y <= (posicoes[i].y + posicoes[i].altura)) ||
			(posicoes[aba].x + posicoes[aba].largura) >= posicoes[i].x && (posicoes[aba].x + posicoes[aba].largura) <= (posicoes[i].x + posicoes[i].largura) && posicoes[aba].y >= posicoes[i].y && posicoes[aba].y <= (posicoes[i].y + posicoes[i].largura) ||
			(posicoes[aba].x + posicoes[aba].largura) >= posicoes[i].x && (posicoes[aba].x + posicoes[aba].largura) <= (posicoes[i].x + posicoes[i].largura) && (posicoes[aba].y + posicoes[aba].altura) >= posicoes[i].y && (posicoes[aba].y + posicoes[aba].altura) < (posicoes[i].y + posicoes[i].altura)){
				if(dx != 0){
					dx++;
					posicoes[aba].x--;
				}
					
				if(dy != 0){
					dy++;
					posicoes[aba].y--;
				}
				
				if(*parede) break;
				
				temtela = 1;
				move(posicoes[i].x, posicoes[i].y, (dx-1), (dy-1), posatual, dxerro, dyerro, posicoes, xmax, ymax, parede);
			}
		}
	}
	
	
}

//#######################################################################################################################

int main(){
	
	FILE *entrada = fopen("entrada.txt", "r");
	FILE *saida = fopen("saida.txt", "w+");
	char comando[15]="Aleatorio";
	int posatual=0, i, xmax, ymax;
	
	struct posicao posicoes[256];	
	
	if(entrada == NULL){
		printf("Nao foi possivel abrir o arquivo de entrada.");
		exit(1);
	}
	

	while(!(feof(entrada))){
		int pcomando=1;
		
		if((comando[0] >= '0' && comando[0] <= '9')){
			sscanf(comando, "%d", &xmax);
			fscanf(entrada, "%d", &ymax);
		}else{
			fscanf(entrada, "%d %d", &xmax, &ymax);
		}
				
		strcpy (comando, "Aleatorio");
		
		while(!(comando[0] > '0' && comando[0] < '9')){
			
			if(feof(entrada))
				break;
			
			fscanf(entrada, "%s", comando);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			if(strcmp(comando, "ABRE")==0){
				abre(entrada, saida, &posatual, xmax, ymax, posicoes, pcomando);
			}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			if(strcmp(comando, "FECHA")==0){
				fecha(entrada, saida, &posatual, xmax, ymax, posicoes, pcomando);	
			}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			if(strcmp(comando, "REDIMENSIONA")==0){
				redimensiona(entrada, saida, &posatual, xmax, ymax, posicoes, pcomando);
			}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			if(strcmp(comando, "MOVE")==0){
				int x, y, dx, dy, dxerro=0, dyerro=0, parede=0;
				fscanf(entrada, "%d %d %d %d", &x, &y, &dx, &dy);
				move(x, y, dx, dy, &posatual, &dxerro, &dyerro, posicoes, xmax, ymax, &parede);
			}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			pcomando++;
			
			
		}
		printf("%d janela(s)\n", posatual);
		fprintf(saida, "%d janela(s)\n", posatual);
		for(i=0; i<posatual; i++){
			printf("%d %d %d %d\n", posicoes[i].x, posicoes[i].y, posicoes[i].largura, posicoes[i].altura);
				fprintf(saida, "%d %d %d %d\n", posicoes[i].x, posicoes[i].y, posicoes[i].largura, posicoes[i].altura);
		}
		posatual=0;
	}
	fclose(entrada);
	fclose(saida);
	return(0);
}

