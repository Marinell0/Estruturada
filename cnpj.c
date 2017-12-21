#include <stdio.h>
#include <stdlib.h>

void cnpj(){

	char cnpj[15];
	int incnpj[14], i, x=0, j=5; 
	
	printf("\nInforme o CPNJ a ser validado : ");
	fgets(cnpj, 15, stdin);
	
	for(i=0; i<14; i++)
		incnpj[i] = cnpj[i]-48;
	
	for(i=0; i<12; i++){
		x = x + incnpj[i]*j--;
		if(j<2) j=9;
	}
	
	x = x % 11;
	
	if(x<2){ 
		x=0;
	}else{
		x = 11-x;
	}
	
	if(x != incnpj[12]){
		printf("CNPJ nao valido!\n\n");
	}else{
		x=0;
		j=6;
		for(i=0; i<13; i++){
			x = x + incnpj[i]*j--;
			if(j<2) j=9;
			
		}
		
		x = x % 11;
	 
		if(x<2){ 
			x=0;
		}else{
			x = 11-x;
		}
		
		printf("\n%d %d\n", x, incnpj[13]);
		if(x != incnpj[13]){
			printf("CNPJ nao valido!\n\n");
		}else{
			printf("CNPJ valido!\n\n");
		}
	}
}		
	
	
