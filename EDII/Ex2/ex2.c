#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//EQUIPE
//Elton
//João Matheus
//Thales Francisco

int hash1(int num){
	int hash = 0;
	hash=num%11;
	return hash;
}

int desloc1(int num){
	int dl = 0;
	dl=(num%2)+1;
	return dl;
}

int hash2(int num){
	int hash = 0;
	hash=num%11;
	return hash;
}

int desloc2(int num){
	int dl = 0;
	dl=(num%2)+1;
	return dl;
}

int hash3(int num){
	int hash = 0;
	hash=num%13;
	return hash;
}

int desloc3(int num){
	int dl = 0;
	dl=(num%4)+1;
	return dl;
}

int hash4(int num){
	int hash = 0;
	hash=num%17;
	return hash;
}

int desloc4(int num){
	int dl = 0;
	dl=(num%3)+1;
	return dl;
}

int main(){
	int lista1[9] = {24,76,39,61,25,10,16,70,53}; //9 elementos
	int lista2[10] = {967,875,985,214,357,248,137,864,247,135}; //10 elementos

	int tabelaE1[11][11], tabela1[11];
	int tabelaE2[11][11], tabela2[11];
	int tabelaE3[13][13], tabela3[13];
	int tabelaE4[17][17], tabela4[17];

	
	memset(tabelaE1,-1,sizeof(tabelaE1));	
	memset(tabela1,-1,sizeof(tabela1));
	memset(tabelaE2,-1,sizeof(tabelaE2));
	memset(tabela2,-1,sizeof(tabela2));
	memset(tabelaE3,-1,sizeof(tabelaE3));
	memset(tabela3,-1,sizeof(tabela3));
	memset(tabelaE4,-1,sizeof(tabelaE4));
	memset(tabela4,-1,sizeof(tabela4));
	int i,j;
	int end;
	
	printf("Lista de Exercicios - Parte 2\n");
	printf("Exercicio 1\n");
	printf("letra a)\n");
	
	for(i=0;i<9;i++){
		j=0;
		end=hash1(lista1[i]);
		
		while(tabelaE1[end][j]>=0){
			j++;
		}
		tabelaE1[end][j]=lista1[i];
	}
	
	for(i=0;i<11;i++){
		printf("%d ->", i);
		for(j=0;j<11;j++){
			if(tabelaE1[i][j]>=0){
				printf(" %d ->",tabelaE1[i][j]);
			}
		}
		printf("\n");
	}
	
	printf("\nletra b)\n");
	
	for(i=0;i<9;i++){
		j=0;
		end=hash1(lista1[i]);
		while(tabela1[end]>=0){
			end+=desloc1(lista1[i]);
			end%=11;
		}
		tabela1[end]=lista1[i];
	}
	
	for(i=0;i<11;i++){
		printf("%d ->", i);
		if(tabela1[i]>=0){
				printf(" %d",tabela1[i]);
		}
		printf("\n");
	}
	
	printf("\nExercicio 2\n");
	printf("letra a)\n");
	
	for(i=0;i<11;i++){
		j=0;
		end=hash2(tabela1[i]);
		
		while(tabelaE2[end][j]>=0){
			j++;
		}
		tabelaE2[end][j]=tabela1[i];
	}
	
	for(i=0;i<11;i++){
		printf("%d ->", i);
		for(j=0;j<11;j++){
			if(tabelaE2[i][j]>=0){
				printf(" %d ->",tabelaE2[i][j]);
			}
		}
		printf("\n");
	}
	
	printf("\nletra b)\n");
	
	for(i=0;i<11;i++){
		if(tabela1[i]<0) continue;
		j=0;
		end=hash2(tabela1[i]);
		while(tabela2[end]>=0){
			end+=desloc2(tabela1[i]);
			end%=11;
		}
		tabela2[end]=tabela1[i];
	}
	
	for(i=0;i<11;i++){
		printf("%d ->", i);
		if(tabela2[i]>=0){
				printf(" %d",tabela2[i]);
		}
		printf("\n");
	}
	
	printf("\nExercicio 3\n");
	printf("letra a)\n");
	
	for(i=0;i<10;i++){
		j=0;
		end=hash3(lista2[i]);
		while(tabelaE3[end][j]>=0){
			j++;
		}
		tabelaE3[end][j]=lista2[i];
	}
	
	for(i=0;i<13;i++){
		printf("%d ->", i);
		for(j=0;j<13;j++){
			if(tabelaE3[i][j]>=0){
				printf(" %d ->",tabelaE3[i][j]);
			}
		}
		printf("\n");
	}
	
	printf("\nletra b)\n");
	
	for(i=0;i<10;i++){
		end=hash3(lista2[i]);
		while(tabela3[end]>=0){
			end+=desloc3(lista2[i]);
			end%=13;
		}
		tabela3[end]=lista2[i];
	}
	
	for(i=0;i<13;i++){
		printf("%d ->", i);
		if(tabela3[i]>=0){
				printf(" %d",tabela3[i]);
		}
		printf("\n");
	}
	
	printf("\nExercicio 4\n");
	printf("letra a)\n");
	
	for(i=0;i<13;i++){
		j=0;
		end=hash4(tabela3[i]);
		
		while(tabelaE4[end][j]>=0){
			j++;
		}
		tabelaE4[end][j]=tabela3[i];
	}
	
	for(i=0;i<17;i++){
		printf("%d ->", i);
		for(j=0;j<11;j++){
			if(tabelaE4[i][j]>=0){
				printf(" %d ->",tabelaE4[i][j]);
			}
		}
		printf("\n");
	}
	
	printf("\nletra b)\n");
	
	for(i=0;i<13;i++){
		if(tabela3[i]<0) continue;
		j=0;
		end=hash4(tabela3[i]);
		while(tabela4[end]>=0){
			end+=desloc4(tabela3[i]);
			end%=11;
		}
		tabela4[end]=tabela3[i];
	}
	
	for(i=0;i<17;i++){
		printf("%d ->", i);
		if(tabela4[i]>=0){
				printf(" %d",tabela4[i]);
		}
		printf("\n");
	}
	
	return 0;
}

