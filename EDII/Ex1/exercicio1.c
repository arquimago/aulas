#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAM 100

char* createLine(char* chave, char* reg){
   	int aux, i;
    char *string = (char *) malloc(sizeof(char) * TAM);
    strcpy(string,chave);
    strcat(string," ");
    strcat(string,reg);
    aux = strlen(string);
    for (i=aux;i<TAM;i++)
        string[i] = ' ';
    return string;
}

int lerS(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r");
	int temp,linha=0,flag=1;
    char index[TAM],reg[TAM];
    while(fscanf(arquivo,"%s",&index)!=EOF){
		fscanf(arquivo,"%s", &reg);
		if(strcmp(index,chave) == 0) {
			printf("Registro encontrado: %s\n", reg);
			flag=0;
			break;
		}
		linha++;
	}
	if(flag){
		printf("Chave não encontrada");
		temp = -1;
	}
	fclose(arquivo);
	return linha;
}

void gravarS(char *arq, char *chave){
	FILE *arquivo;
	arquivo = fopen(arq, "a+");
	char* string = createLine(chave, chave);
	fprintf(arquivo,"%s\n", string);
	fclose(arquivo);
}

void modificarS(char *arq, char *chave, char *new_reg){
	FILE *arquivo = fopen(arq, "r+");
	int linha = lerS("seq.txt", chave);
	char* string = createLine(chave,new_reg);
	fseek(arquivo, linha*100, SEEK_SET);
	fprintf(arquivo, "%s\n", string);
}

void excluirS(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	int linha = lerS("seq.txt", chave);
	char* string;
	char index[TAM],reg[TAM], aux[TAM];
	fseek(arquivo, linha*100, SEEK_SET);
	string = createLine("","");
	fprintf(arquivo, "%s\n", string);
    //Falta a função para ir deslocando as linhas
}

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
