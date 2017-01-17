#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAM 99

char* createLine(char* chave, char* reg){
   	int aux, i;
    char *string = (char *) malloc(sizeof(char) * TAM);
    strcpy(string,chave);
    strcat(string," ");
    strcat(string,reg);
    aux = strlen(string);
    for (i=aux;i<=TAM-1;i++)
        string[i] = ' ';
    string[TAM]='\0';
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
		printf("Chave não encontrada\n");
		temp = -1;
		linha = -1;
	}
	fclose(arquivo);
	return linha;
}

void gravarS(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	int value_index, value_chave, flag = -1, linha = 1;
    char index[TAM],reg[TAM], aux_index[TAM], aux_reg[TAM];
    char* string;
    while(fscanf(arquivo,"%s",&index)!=EOF){
		fscanf(arquivo,"%s", &reg);
		value_index = atoi(index);
		value_chave = atoi(chave);
		if(!flag){
			string = createLine(aux_index, aux_reg);
			fseek(arquivo, (linha-1)*100, SEEK_SET);
			fprintf(arquivo,"%s\n", string);
			strcpy(aux_index,index);
			strcpy(aux_reg,reg);
		}
		else if(value_index >= value_chave) {
			string = createLine(chave, chave);
			fseek(arquivo, (linha-1)*100, SEEK_SET);
			fprintf(arquivo,"%s\n", string);
			strcpy(aux_index,index);
			strcpy(aux_reg,reg);
			flag=0;
		}
		linha++;
	}
	if(flag){
		string = createLine(chave, chave);
		fprintf(arquivo,"%s\n", string);
	}else{
		string = createLine(aux_index, aux_reg);
		fprintf(arquivo,"%s\n", string);
	}

	fclose(arquivo);
}

void modificarS(char *arq, char *chave, char *new_reg){
	FILE *arquivo = fopen(arq, "r+");
	int linha = lerS(arq, chave);
	char* string = createLine(chave, new_reg);
	fseek(arquivo, linha*100, SEEK_SET);
	fprintf(arquivo, "%s\n", string);
	fclose(arquivo);
}

void excluirS(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	int linha = lerS(arq, chave);
	char* string;
    char index[TAM],reg[TAM];
	linha++;
	fseek(arquivo, (linha)*100, SEEK_SET);
	if(linha != 0){
	   	while(fscanf(arquivo,"%s",&index)!=EOF){
			fscanf(arquivo,"%s", &reg);
			string = createLine(index, reg);
			fseek(arquivo, (linha-1)*100, SEEK_SET);
			fprintf(arquivo,"%s\n", string);
			linha++;
			fseek(arquivo, (linha)*100, SEEK_SET);
		}
		//Limpa a ultima linha
		string = createLine("","");
		fseek(arquivo, (linha-1)*100, SEEK_SET);
		fprintf(arquivo,"%s\n", string);
	}else{
		//Chave não encontrada!
	}
	fclose(arquivo);
}

int lerI(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	FILE *aux_arquivo = fopen("ind.ind", "r+");
    char index[TAM],reg[TAM];	
	int linha = -1, flag=1;
	while(fscanf(aux_arquivo,"%s",&index)!=EOF){
		fscanf(aux_arquivo,"%s", &reg);
		if(strcmp(index,chave) == 0){
			linha = atoi(reg);
			fseek(arquivo,linha*100,SEEK_SET);
			fscanf(arquivo,"%s",&index);
			fscanf(arquivo,"%s",&reg);
			printf("Registro encontrado: %s\n", reg);
			flag=0;
			break;
		}
	}if(flag){
		printf("Chave não encontrada\n");
	}
	return linha;
}

void gravarI(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	char *string;
    char index[TAM],reg[TAM], aux[10];
    int linha = 0;
    while(fscanf(arquivo,"%s",&index)!=EOF){
		fscanf(arquivo,"%s", &reg);
		if(strcmp(index,"#") == 0){
			gravarS("ind.ind",chave);
			sprintf(aux,"%d", linha);
			modificarS("ind.ind",chave,aux);
			string = createLine(chave, chave);
			fseek(arquivo,linha*100,SEEK_SET);
			fprintf(arquivo,"%s\n",string);
			break;
		}
		linha++;
	}
	return;
}

void modificarI(char *arq, char *chave, char *new_reg){
	FILE *arquivo = fopen(arq, "r+");
	int linha = lerI(arq,chave);
	if (linha != -1){
		char *string = createLine(chave, new_reg);
		fseek(arquivo, linha*100, SEEK_SET);
		fprintf(arquivo, "%s\n", string);
	}else{
		printf("Chave não encontrada\n");
	}
	return;
}

void excluirI(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	int linha = lerI(arq, chave);
	if(linha != -1){
		excluirS("ind.ind", chave);
		char *string = createLine("#","#");
		fseek(arquivo,linha*100,SEEK_SET);
		fprintf(arquivo, "%s\n", string);
	}else{
		printf("Chave não encontrada\n");
	}
}

int hash(char *chave){
	int hash = atoi(chave);
	hash%=10007;
	//sim, 10.007 é primo perguntei ao Wolfram Alpha
	return hash;
}

void lerD(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	int linha = hash(chave);
	fseek(arquivo, (linha-1)*100, SEEK_SET);
    char index[TAM],reg[TAM];
	fscanf(arquivo,"%s", &index);
	fscanf(arquivo,"%s", &reg);
	printf("Registro encontrado: %s\n", reg);
	return;
}

void gravarD(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	int linha = hash(chave);
	fseek(arquivo, (linha-1)*100, SEEK_SET);
	char* string = createLine(chave,chave);
	fprintf(arquivo, "%s\n", string);
	return;
}

void modificarD(char *arq, char *chave, char *new_reg){
	FILE *arquivo = fopen(arq, "r+");
	int linha = hash(chave);
	fseek(arquivo, (linha-1)*100, SEEK_SET);
	char* string = createLine(chave,new_reg);
	fprintf(arquivo, "%s\n", string);
	return;
}

void excluirD(char *arq, char *chave){
	FILE *arquivo = fopen(arq, "r+");
	char *string;
	int linha = hash(chave);
	fseek(arquivo, (linha-1)*100, SEEK_SET);
	string = createLine("","");
	fprintf(arquivo, "%s\n", string);
	return;
}


int main(){

    int i;
    char *string;
    FILE *arquivo;
    arquivo = fopen("seq.txt", "a+");
    fclose(arquivo);
    arquivo = fopen("ind.txt", "a+");
    string = createLine("#","#");
    for(i=0;i<10000;i++){
        fprintf(arquivo, "%s\n", string);
    }    
    fclose(arquivo);
    arquivo = fopen("ind.ind", "a+");
    fclose(arquivo);
    arquivo = fopen("dir.txt", "a+");
    string = createLine("","");
    for(i=0;i<10000;i++){
        fprintf(arquivo, "%s\n", string);
    }
    fclose(arquivo);

    //Testar funções
    
    return 0;
}
