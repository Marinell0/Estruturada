#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoaFisica{
	char nome[100];
	char logradouro[100];
	char numero[10];
	char complemento[100];
	char bairro[100];
	char CEP[10];
	unsigned long int CPF;
	unsigned long int data;
}pessoafisica;

typedef struct pessoaJuridica{
	char nomeEmpresa[100];
	char logradouro[100];
	char numero[10];
	char complemento[100];
	char bairro[100];
	char CEP[10];
	unsigned long int CNPJ;
}pessoajuridica;

pessoafisica PF[100];
pessoajuridica PJ[100];
int i=0, j=0;

void menu(){
	system("clear");
	printf("######################################\n");
	printf("#                                    #\n");
	printf("#  0 - Sair                          #\n");
	printf("#  1 - Cadastrar                     #\n");
	printf("#  2 - Excluir                       #\n");
	printf("#  3 - Editar                        #\n");
	printf("#  4 - Consultar                     #\n");
	printf("#                                    #\n");
	printf("######################################\n");
}

void pfpj(){
	printf("\n\n");
	printf("##############################\n");
	printf("#                            #\n");
	printf("#  0 - Voltar                #\n");
	printf("#  1 - PF                    #\n");
	printf("#  2 - PJ                    #\n");
	printf("#                            #\n");
	printf("##############################\n");
	printf("\nSua opcao: ");
}

void leituraPF(){
	//printf("======================= Pessoa Fisica ============================\n\n");
	
	FILE *pf;
	pf = fopen("pf.txt", "r");
	
	
	while((fgets(PF[i].nome, 100, pf)) != NULL){
		//printf("Nome: %s", PF[i].nome);
		fgets(PF[i].logradouro, 100, pf);
		//printf("Logradouro: %s", PF[i].logradouro);
		fgets(PF[i].numero, 100, pf);
		//printf("Numero: %s", PF[i].numero);
		fgets(PF[i].complemento, 100, pf);
		//printf("Complemento: %s", PF[i].complemento);
		fgets(PF[i].bairro, 100, pf);
		//printf("Bairro: %s", PF[i].bairro);
		fgets(PF[i].CEP, 100, pf);
		//printf("CEP: %s", PF[i].CEP);
		fscanf(pf, "%lu", &PF[i].CPF);
		//printf("CPF: %lu\n", PF[i].CPF);
		fscanf(pf, "%lu\n", &PF[i].data);
		//printf("Data de nascimento: %lu\n", PF[i].data);
		//printf("\n===================================\n\n");
		i++;
	}
	
	fclose(pf);
}

void leituraPJ(){
	
	FILE *pj;
	pj = fopen("pj.txt", "r");
	
	
	while((fgets(PJ[j].nomeEmpresa, 100, pj)) != NULL){
		//printf("Nome: %s", PJ[j].nomeEmpresa);
		fgets(PJ[j].logradouro, 100, pj);
		//printf("Logradouro: %s", PJ[j].logradouro);
		fgets(PJ[j].numero, 100, pj);
		//printf("Numero: %s", PJ[j].numero);
		fgets(PJ[j].complemento, 100, pj);
		//printf("Complemento: %s", PJ[j].complemento);
		fgets(PJ[j].bairro, 100, pj);
		//printf("Bairro: %s", PJ[j].bairro);
		fgets(PJ[j].CEP, 100, pj);
		//printf("CEP: %s", PJ[j].CEP);
		fscanf(pj, "%lu\n", &PJ[j].CNPJ);
		//printf("CNPJ: %lu\n", PJ[j].CNPJ);
		//printf("\n===================================\n\n");
		j++;
	}
	
	fclose(pj);
}

void escritaPF(){
	int aux=0;
	FILE *pf;
	pf = fopen("pf.txt", "w+");
	for(aux=0; aux<=i; aux++){
		fprintf(pf, "%s", PF[aux].nome);
		fprintf(pf, "%s", PF[aux].logradouro);
		fprintf(pf, "%s", PF[aux].numero);
		fprintf(pf, "%s", PF[aux].complemento);
		fprintf(pf, "%s", PF[aux].bairro);
		fprintf(pf, "%s", PF[aux].CEP);
		fprintf(pf, "%lu\n", PF[aux].CPF);
		fprintf(pf, "%lu\n", PF[aux].data);
	}
	fclose(pf);
}

void escritaPJ(){
}



int cadastramentoPF(){
	printf("\n");
	getchar();
	printf("Nome: ");
	fgets(PF[i].nome, 100, stdin);
	printf("Logradouro: ");
	fgets(PF[i].logradouro, 100, stdin);
	printf("Numero: ");
	fgets(PF[i].numero, 100, stdin);
	printf("Complemento: ");
	fgets(PF[i].complemento, 100, stdin);
	printf("Bairro: ");
	fgets(PF[i].bairro, 100, stdin);
	printf("CEP: ");
	fgets(PF[i].CEP, 100, stdin);
	printf("CPF: ");
	scanf("%lu", &PF[i].CPF);
	printf("Data de nascimento: ");
	scanf("%lu", &PF[i].data);
	
	escritaPF();
}

void cadastramentoPJ(){
}


void excluirPF(){
	int aux;
	printf("CPF de quem quer excluir: ");
	unsigned long int CPF;
	scanf("%lu", &CPF);
	
	for(aux=0; aux<=i; aux++){
		if(PF[aux].CPF == CPF){
			for(aux=aux; aux<i; aux++){
				strcpy(PF[aux].nome, PF[aux+1].nome);
				strcpy(PF[aux].logradouro, PF[aux+1].logradouro);
				strcpy(PF[aux].numero, PF[aux+1].numero);
				strcpy(PF[aux].complemento, PF[aux+1].complemento);
				strcpy(PF[aux].bairro, PF[aux+1].bairro);
				strcpy(PF[aux].CEP, PF[aux+1].CEP);
				PF[aux].CPF = PF[aux+1].CPF;
				PF[aux].data = PF[aux+1].data;
			}
			i--;
			i--;
		}
	}
	
	escritaPF();
	i++;
	
}

void excluirPJ(){
}

void editarPF(){
	int aux,x=1;
	printf("CPF de quem quer editar: ");
	unsigned long int CPF;
	scanf("%lu", &CPF);
	for(aux=0; aux<=i; aux++){
		if(PF[aux].CPF == CPF){
			while(x){
				system("clear");
				printf("\n===================================\n\n");
				printf("Nome: %s", PF[aux].nome);
				printf("Logradouro: %s", PF[aux].logradouro);
				printf("Numero: %s", PF[aux].numero);
				printf("Complemento: %s", PF[aux].complemento);
				printf("Bairro: %s", PF[aux].bairro);
				printf("CEP: %s", PF[aux].CEP);
				printf("CPF: %lu\n", PF[aux].CPF);
				printf("Data de nascimento: %lu\n", PF[aux].data);
				printf("\n===================================\n\n");
				printf("######################################\n");
				printf("#                                    #\n");
				printf("#  0 - Sair                          #\n");
				printf("#  1 - Nome                          #\n");
				printf("#  2 - Logradouro                    #\n");
				printf("#  3 - Numero                        #\n");
				printf("#  4 - Complemento                   #\n");
				printf("#  5 - Bairro                        #\n");
				printf("#  6 - CEP                           #\n");
				printf("#  7 - CPF                           #\n");
				printf("#  8 - Data de nascimento            #\n");
				printf("#                                    #\n");
				printf("######################################\n\n");
				printf("Sua opcao: ");
				int op2;
				scanf("%d", &op2);
				getchar();
				switch(op2){
					case 0:
						x=0;
					break;
				
					case 1:
						printf("\nNovo Nome: ");
						fgets(PF[aux].nome, 100, stdin);
					break;
				
					case 2:
						printf("\nNovo Logradouro: ");
						fgets(PF[aux].logradouro, 100, stdin);
					break;
				
					case 3:
						printf("\nNovo Numero: ");
						fgets(PF[aux].numero, 100, stdin);
					break;
				
					case 4:
						printf("\nNovo Complemento: ");
						fgets(PF[aux].complemento, 100, stdin);
					break;
				
					case 5:
						printf("\nNovo Bairro: ");
						fgets(PF[aux].bairro, 100, stdin);
					break;
				
					case 6:
						printf("\nNovo CEP: ");
						fgets(PF[aux].CEP, 100, stdin);
					break;
				
					case 7:
						printf("\nNovo CPF: ");
						scanf("%lu", &PF[aux].CPF);
					break;
				
					case 8:
						printf("\nNova data de nascimento: ");
						scanf("%lu", &PF[aux].data);
					break;
				
							
				}
			}
		}
	}
	
	escritaPF();
}

void editarPJ(){
}

void consultarPF(){
}

void consultarPJ(){
}

void main(){
	int x=1;
	leituraPF();
	leituraPJ();
	
	while(1){
		x=1;
		menu();
		int op=0, op2;
		printf("\nOpcao: ");
		scanf("%d", &op);
		switch(op){
	
			case 0:
				exit(0);
			break;
		
			case 1:
				while(x){
					pfpj();
					scanf("%d", &op2);
					switch(op2){
						case 0:
							x=0;
						break;
					
						case 1:
							cadastramentoPF();
						break;
				
						case 2:
							cadastramentoPJ();
						break;
					}
				}
			break;
		
			case 2:
				while(x){
					pfpj();
					scanf("%d", &op2);
					switch(op2){
						case 0:
							x=0;
						break;
					
						case 1:
							excluirPF();
						break;
				
						case 2:
							excluirPJ();
						break;
					}
				}
				
			break;
			
			case 3:
				while(x){
					pfpj();
					scanf("%d", &op2);
					switch(op2){
						case 0:
							x=0;
						break;
					
						case 1:
							editarPF();
						break;
				
						case 2:
							editarPJ();
						break;
					}
				}
			break;
			
			case 4: 
				while(x){
					pfpj();
					scanf("%d", &op2);
					switch(op2){
						case 0:
							x=0;
						break;
					
						case 1:
							consultarPF();
						break;
				
						case 2:
							consultarPJ();
						break;
					}
				}
			break;
			
		}
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

