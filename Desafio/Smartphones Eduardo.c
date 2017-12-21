#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tela{
	int xmax;
	int ymax;
};

struct posicao{
	int x;
	int y;
	int largura;
	int altura;
};

struct tela telas[10];
struct posicao posicoes[256];

//#######################################################################################################################

void abre(FILE *entrada, int *atual, int tela){
	int x, y, largura, altura;
	int negado=0, i;
	
	fscanf(entrada, "%d %d %d %d", &x, &y, &largura, &altura);
	
	if(x < 0 || y < 0 || (x + largura) > telas[tela].xmax || (y + altura) > telas[tela].ymax){
		printf("--Aba nao foi criada porque passa os limites da tela\n");/////////////////////////////////////////////////////////
		return;
	}
	
	//------------------------ FOR PARA VER SE HÁ UMA TELA DENTRO DA OUTRA --------------------------------------------------
	
	for(i=0; i<*atual; i++){
		if(((posicoes[i].x <= x && x <= (posicoes[i].x + posicoes[i].largura)) && (posicoes[i].y <= y && y <= (posicoes[i].y + posicoes[i].altura))) || 
		((x <= posicoes[i].x && (posicoes[i].x + posicoes[i].largura) <= (x + largura)) && (y <= posicoes[i].y && (posicoes[i].y + posicoes[i].altura)) <= (y + altura))){ 
			negado=1;
			printf("--Aba nao foi criada porque sobrepoe outra tela\n");//////////////////////////////////////////////////////////
			break;
		}
	}
	
	//-------------------------- FOR PARA VER SE AS PONTAS NÃO ENTRAM DENTRO DE OUTRA TELA ----------------------------------
	
	for(i=0; i<*atual; i++){
		if((x + largura) >= posicoes[i].x && (x + largura) <= (posicoes[i].x + posicoes[i].largura) && y >= posicoes[i].y && y <= (posicoes[i].y + posicoes[i].altura) ||
		(x >= posicoes[i].x && x <= (posicoes[i].x + posicoes[i].largura) && y >= posicoes[i].y && y <= (posicoes[i].y + posicoes[i].altura)) ||
		((y + altura) >= posicoes[i].y && (y + altura) <= (posicoes[i].y + posicoes[i].largura) && x >= posicoes[i].x && x <= (posicoes[i].x + largura))){
			negado=1;
			printf("--Aba nao foi criada porque sobrepoe outra tela\n");//////////////////////////////////////////////////////////
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
		printf("--Aba nao foi criada porque sobrepoe outra tela\n");//////////////////////////////////////////////////////////
	}else{
		posicoes[*atual].x = x;
		posicoes[*atual].y = y;
		posicoes[*atual].largura = largura;
		posicoes[*atual].altura = altura;
		++*atual;	
	}	
	
}

//#######################################################################################################################

void fecha(FILE *entrada, int *atual){
	int i, j, x, y, existetela=0;
	
	fscanf(entrada, "%d %d", &x, &y);
	
	for(i=0; i<*atual; i++)
		printf("Telas: x = %d, y = %d, largura = %d, altura = %d\n", posicoes[i].x, posicoes[i].y, posicoes[i].largura, posicoes[i].altura);///////////////////////////////////////
	
	for(i=0; i<*atual; i++){
		if(x == posicoes[i].x && y == posicoes[i].y){
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
		printf("A tela com posicao %d %d nao existe.\n", x, y);/////////////////////////////////////////////////////
	}
	
	for(i=0; i<*atual; i++)
		printf("Telas apos fecha: x = %d, y = %d, largura = %d, altura = %d\n", posicoes[i].x, posicoes[i].y, posicoes[i].largura, posicoes[i].altura);	////////////////////////////
	
}

//#######################################################################################################################

void redimensiona(FILE *entrada, int *atual, int tela){
	int x, y, largura, altura, i, negado=0;
	
	fscanf(entrada, "%d %d %d %d", &x, &y, &largura, &altura);
	
	if((x + largura) > telas[tela].xmax || (y + altura) > telas[tela].ymax){
		printf("redimensionar sai da tela\n");///////////////////////////////////////////////////////////////
		return;
	}
	
	//----------------------------------------- FOR PARA TESTAR SE AS PONTAS ENTRAM EM OUTRA TELA ---------------------------
	
	for(i=0; i<=*atual; i++){
		if (x == posicoes[i].x && y == posicoes[i].y){
			if (i == (*atual - 1)) break;
			i++;
		}
		if((x + largura) >= posicoes[i].x && (x + largura) <= (posicoes[i].x + posicoes[i].largura) && y >= posicoes[i].y && y <= (posicoes[i].y + altura) || 
		((y + altura) >= posicoes[i].y && (y + altura) <= (posicoes[i].y + posicoes[i].largura) && x >= posicoes[i].x && x <= (posicoes[i].x + largura)) ||
		(posicoes[i].x >= x && posicoes[i].x <= (x + largura)) && (posicoes[i].y >= y && posicoes[i].y <= (y + altura))){
			negado=1;
			break;
		}
	}
	
	//-----------------------------------------------------------------------------------------------------------------------
	
	for(i=0; i<=*atual; i++){
		if((x >= posicoes[i].x && (x + largura) <= (posicoes[i].x + posicoes[i].largura)) && (y <= posicoes[i].y &&  (y + altura) >= (posicoes[i].y + posicoes[i].altura)) ||
		(y >= posicoes[i].y && (y + altura) <= (posicoes[i].y + posicoes[i].altura)) && (x <= posicoes[i].x && (x + largura) >= (posicoes[i].x + posicoes[i].largura))){
			negado=1;
			break;
		}
	}
	
	if(negado){
		printf("A tela x=%d e y=%d nao foi redimensionada\n", posicoes[i].x, posicoes[i].y);///////////////////////////////
	}else{
		for(i=0; i<=*atual; i++){
			if(x == posicoes[i].x && y == posicoes[i].y){
				posicoes[i].largura = largura;
				posicoes[i].altura = altura;
				break;
			}
		}
	}
	
}

//#######################################################################################################################

void move(int x, int y, int dx, int dy, int *posatual, int tela, int *dxerro, int *dyerro){

	int i, aba;
	int horizontal = dx;
	int vertical = dy;
	
	for(i=0; i<*posatual; i++){
		if(x == posicoes[i].x && y == posicoes[i].y){
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
	
	
	for(dx=dx, dy=dy; dx>0 && dy>0 ; dx--, dy--){
		if(dx <= 0) dx = 0;
		if(dy <= 0) dy = 0;
		
		posicoes[aba].x++;
		posicoes[aba].y++;
		
		if(posicoes[aba].x < 0 || posicoes[aba].y < 0 || (posicoes[aba].x + posicoes[aba].largura) > telas[tela].xmax || (posicoes[aba].y + posicoes[aba].altura) > telas[tela].ymax){
			dx++;
			dy++;
			*dxerro = dx;
			*dyerro = dy;
			return;
		}
		
		for(i=0; i<=*posatual; i++){
			if(i == aba) i++;
			
			if((posicoes[aba].x + posicoes[aba].largura) >= posicoes[i].x && (posicoes[aba].x + posicoes[aba].largura) <= (posicoes[i].x + posicoes[i].largura) && posicoes[aba].y >= posicoes[i].y && posicoes[aba].y <= (posicoes[i].y + posicoes[aba].altura) ||
			(posicoes[aba].x >= posicoes[i].x && posicoes[aba].x <= (posicoes[i].x + posicoes[i].largura) && posicoes[tela].y >= posicoes[i].y && posicoes[tela].y <= (posicoes[i].y + posicoes[i].altura)) ||
			((posicoes[aba].y + posicoes[aba].altura) >= posicoes[i].y && (posicoes[aba].y + posicoes[aba].altura) <= (posicoes[i].y + posicoes[i].largura) && posicoes[aba].x >= posicoes[i].x && posicoes[aba].x <= (posicoes[i].x + posicoes[aba].largura)) ||
			(posicoes[aba].x >= posicoes[i].x && (posicoes[aba].x + posicoes[aba].largura) >= (posicoes[i].x + posicoes[i].largura) && posicoes[aba].y <= posicoes[i].y && (posicoes[aba].y + posicoes[aba].altura) >= (posicoes[i].y + posicoes[i].altura))){
				dx++;
				dy++;
				move(posicoes[i].x, posicoes[i].y, dx, dy, posatual, tela, dxerro, dyerro);
			}
		}
		
		
			
	}
	
	
	
	
}

//#######################################################################################################################

int main(){
	
	FILE *entrada = fopen("entrada.txt", "r");
	char comando[15]="Aleatorio";
	int tela=0, posatual=0, i;
	
	if(entrada == NULL){
		printf("Nao foi possivel abrir o arquivo de entrada.");
		exit(1);
	}

	while(!(feof(entrada)) && tela<10){
		int pcomando=0;
		
		if((comando[0] >= '0' && comando[0] <= '9') && tela!= 0){
			sscanf(comando, "%d", &telas[tela].xmax);
			fscanf(entrada, "%d", &telas[tela].ymax);
		}else{
			fscanf(entrada, "%d %d", &telas[tela].xmax, &telas[tela].ymax);
		}
		printf("%d %d\n", telas[tela].xmax, telas[tela].ymax);
		
		strcpy (comando, "Aleatorio");
		
		while(!(comando[0] > '0' && comando[0] < '9')){
			
			if(feof(entrada))
				break;
			
			fscanf(entrada, "%s", comando);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			if(strcmp(comando, "ABRE")==0){
				abre(entrada, &posatual, tela);
			}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			if(strcmp(comando, "FECHA")==0){
				fecha(entrada, &posatual);	
			}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			if(strcmp(comando, "REDIMENSIONA")==0){
				redimensiona(entrada, &posatual, tela);
			}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			if(strcmp(comando, "MOVE")==0){
				int x, y, dx, dy, dxerro=0, dyerro=0;
				fscanf(entrada, "%d %d %d %d", &x, &y, &dx, &dy);
				move(x, y, dx, dy, &posatual, tela, &dxerro, &dyerro);
				if(dxerro == 0 || dyerro == 0){
					printf("A tela deixou de mover em x:%d e em y:%d\n", posicoes[(posatual-1)].x, posicoes[(posatual-1)].y);
				}
			}
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			pcomando++;
			
			
		}
		for(i=0; i<posatual; i++){
				printf("\n\n\n");
				printf("\nTelas: x=%d, y=%d, tamanho=%d, altura=%d", posicoes[i].x, posicoes[i].y, posicoes[i].largura, posicoes[i].altura);
		}
		posatual=0;
		tela++;
	}
	
	return(0);
}

