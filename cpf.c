#include <stdio.h>
#include <stdlib.h>

void cpf(){
	
	int incpf[11], i, j=10, x=0; 
	char cpf[12]; 
	
	printf("Informe o CPF a ser validado : ");
	fgets(cpf, 12, stdin);
	
	for(i=0; i<11; i++)
		incpf[i] = cpf[i]-48;

	printf("\n");
			
	
	//###############################################################################################
	
	
	for(i=0; i<9; i++)
		x = x + incpf[i]*j--;
	
	
		
	x = x % 11;
	x = 11-x;
	
	
	if(x >= 10)
		x=0;
	

	
	if(incpf[9] != x){
		printf("\n\nCPF nao e valido!\n\n");
	}else{
		x=0;
		j=11;
		for(i=0; i<10; i++)
			x = x + incpf[i]*j--;
		
		
		x = x % 11;
		x = 11-x;
		
			
		if(incpf[10] != x){
			printf("\n\nCPF nao e valido!\n\n");
		}else{
			printf("\n\nCPF e valido!\n\n");
		}
	 }	
		
}
