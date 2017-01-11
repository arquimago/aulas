#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int lerS(char *arq, int chave){
	FILE *arquivo;
	int temp,flag;
	flag=1;
	arquivo = fopen(arq, "r");
	while(fscanf(arquivo,"%d",temp)!=EOF){
		fscanf(arquivo,"%d", temp);
		if(temp == chave) {
			printf("%d", temp);
			flag=0;
			break;
		}
	}
	if(flag){
		printf("Chave não encontrada");
		temp = -1;
	}
	fclose(arquivo);
	return temp;
}

void gravarS(char *arq, int chave){
	FILE *arquivo;
	arquivo = fopen(arq, "a+");
	fprintf(arquivo,"%d %d\n",chave, chave);
	fclose(arquivo);
}

void modificarS(char *arq, int chave){
	
	
}

void excluirS(char *arq, int chave){}

void lerI(char *arq, int chave){}

void gravarI(char *arq, int chave){}

void modificarI(char *arq, int chave){}

void excluirI(char *arq, int chave){}

void lerD(char *arq, int chave){}

void gravarD(char *arq, int chave){}

void modificarD(char *arq, int chave){}

void excluirD(char *arq, int chave){}


int main(){
	FILE *arquivo;
	arquivo = fopen("seq.txt", "a+");
	fclose(arquivo);
	arquivo = fopen("ind.txt", "a+");
	fclose(arquivo);
	arquivo = fopen("ind.ind", "a+");
	fclose(arquivo);
	arquivo = fopen("dir.txt", "a+");
	fclose(arquivo);
	
	
	
	return 0;
}
