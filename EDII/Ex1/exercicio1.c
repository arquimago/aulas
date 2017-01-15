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
		linha = -1;
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
	fclose(arquivo);
}

void excluirS(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	int linha = lerS("seq.txt", chave);
	char* string;
	char index[TAM],reg[TAM], aux[TAM];
	fseek(arquivo, linha*100, SEEK_SET);
	string = createLine("","");
	fprintf(arquivo, "%s\n", string);
    //acho que o while abaixo resolve a subida das linhas
	while(fscanf(arquivo,"%[^\n]s",string);!=EOF){
		fseek(arquivo, linha*100, SEEK_SET);
		fprintf(arquivo, "%s\n", string);
		linha++;
	}
	//as linhas abaixo são pra remover a linha duplicada que fica no final
	linha--;
	fseek(arquivo, linha*100, SEEK_SET);
	string = createLine("","");
	fprintf(arquivo, "%s\n", string);
	
	fclose(arquivo);
}

void lerI(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r");
	char *reg;
	int linha = lerS("ind.ind",chave);
	if(linha>=0) {
		fseek(arquivo, linha*100, SEEK_SET);
		fscanf(arquivo,"%s", &reg);
		printf("Registro encontrado: %s\n", reg);	
	}else{
		printf("Registro não encontrado";
	}
	return;
}

void gravarI(char *arq, char *chave){
	return;
}

void modificarI(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	char *reg;
	int linha = lerS("ind.ind",chave);
	
	
	return;
}

void excluirI(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	char *reg;
	int linha = lerS("ind.ind",chave);
	
	//no final usar excluirS no "ind.ind" 
	return;
}

int hash(char *chave){
	int hash = 0;
	int i;
	for(i=0;i<strlen(chave);i++){
		hash+=(chave[i]-60);
		//um char numerico -60 dá como resultado seu valor em int
	}
	hash%=10007;
	//sim, 10.007 é primo perguntei ao Wolfram Alpha
	return hash;
}

void lerD(char *arq, char *chave){
	int linha = hash(chave);
	fseek(arquivo, linha*100, SEEK_SET);
	
	return;
}

void gravarD(char *arq, char *chave){
	int linha = hash(chave);
	fseek(arquivo, linha*100, SEEK_SET);
	
	return;
}

void modificarD(char *arq, char *chave){
	int linha = hash(chave);
	fseek(arquivo, linha*100, SEEK_SET);
	
	return;
}

void excluirD(char *arq, char *chave){
	int linha = hash(chave);
	fseek(arquivo, linha*100, SEEK_SET);
	
	return;
}


int main(){
	int i;
	FILE *arquivo;
	arquivo = fopen("seq.txt", "a+");
	fclose(arquivo);
	arquivo = fopen("ind.txt", "a+");
	fclose(arquivo);
	arquivo = fopen("ind.ind", "a+");
	fclose(arquivo);
	arquivo = fopen("dir.txt", "a+");
	for(i=0;i<10000;i++){
		string = createLine("","");
		fprintf(arquivo, "%s\n", string);
	}
	fclose(arquivo);

  return 0;
}
