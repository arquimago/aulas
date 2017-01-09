#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void lerS(char *arq, int chave){}

void gravarS(char *arq, int chave){}

void modificarS(char *arq, int chave){}

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
	
	arquivo = fopen("arquivo.txt", "w+");
	
	fclose(arquivo);
	return 42;
}
