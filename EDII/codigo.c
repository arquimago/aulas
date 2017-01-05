//Elton
//João Mateus
//Thales Francisco

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAM 300

int main(){
	FILE *arquivo;
	
	arquivo = fopen("arquivo.txt", "w+");
	char string[TAM];
	int tamanho;
	while(1){
		printf("Digite um texto, para sair digite 0: ");
		fgets(string,TAM,stdin);
		if(string[0]=='0') break;
		tamanho = (int)strlen(string);
		string[tamanho]='\0';
		tamanho--;
		fprintf(arquivo, "%d\t%s", tamanho, string);
	}
	fclose(arquivo);
	return 42;
}
