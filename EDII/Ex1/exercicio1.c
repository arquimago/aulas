#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define TAM 99

//EQUIPE
//Elton
//João Matheus
//Thales Francisco

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
    //Percorre arquivo
    while(fscanf(arquivo,"%s",&index)!=EOF){
		fscanf(arquivo,"%s", &reg);
		//Se encontrar a chave desejada, imprima
		if(strcmp(index,chave) == 0) {
			printf("Registro encontrado: %s\n", reg);
			flag=0;
			break;
		}
		linha++;
	}
	//Se não encontrar, imprima
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
    //Percorre arquivo
    while(fscanf(arquivo,"%s",&index)!=EOF){
		fscanf(arquivo,"%s", &reg);
		value_index = atoi(index);
		value_chave = atoi(chave);
		//Salve a proxima chave na linha anterior
		if(!flag){
			string = createLine(aux_index, aux_reg);
			fseek(arquivo, (linha-1)*100, SEEK_SET);
			fprintf(arquivo,"%s\n", string);
			strcpy(aux_index,index);
			strcpy(aux_reg,reg);
		}
		//Se a chave lida for maior ou igual a chave a ser inserida, insira a nova chave no lugar e salve a seguinte em um aux
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
	//Se for a ultima linha, insira no final do arquivo.
	if(flag){
		string = createLine(chave, chave);
		fprintf(arquivo,"%s\n", string);
	}else{//Se não for a ultima linha, insira a variável que faltou do while
		string = createLine(aux_index, aux_reg);
		fprintf(arquivo,"%s\n", string);
	}
	fclose(arquivo);
}

void modificarS(char *arq, char *chave, char *new_reg){//Encontra chave e modifica
	FILE *arquivo = fopen(arq, "r+");
	int linha = lerS(arq, chave);
	char* string = createLine(chave, new_reg);
	fseek(arquivo, linha*100, SEEK_SET);
	fprintf(arquivo, "%s\n", string);
	fclose(arquivo);
}

void excluirS(char *arq, char *chave){//Encontra chave, remove e organiza o arquivo
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
	//Percorre o arquivo ind.ind
	while(fscanf(aux_arquivo,"%s",&index)!=EOF){
		fscanf(aux_arquivo,"%s", &reg);
		//Encontra chave
		if(strcmp(index,chave) == 0){
			linha = atoi(reg);
			//Vai até a linha e imprime o valor de reg
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
    //Percorre ind.txt
    while(fscanf(arquivo,"%s",&index)!=EOF){
		fscanf(arquivo,"%s", &reg);
		//Encontra uma posição vazia (# # = Sem dados)
		if(strcmp(index,"#") == 0){
			//Grava a chave no ind.ind
			gravarS("ind.ind",chave);
			sprintf(aux,"%d", linha);
			//Modifica no ind.ind com a linha no reg
			modificarS("ind.ind",chave,aux);
			//Salva a chave no arquivo ind.txt
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
	//Procura se exite a chave no ind.txt
	int linha = lerI(arq,chave);
	if (linha != -1){
		//Vai até a linha e altera o valor
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
	//Procura se exite a chave no ind.txt
	int linha = lerI(arq, chave);
	if(linha != -1){
		//Exclui a chave no ind.ind
		excluirS("ind.ind", chave);
		//Exclui a chave no ind.txt
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

    //Exercicio 01

    //OBS: Será impresso na tela algumas vezes "Resultados Encontrados"
    //Isso ocorre, pois utilizamos a mesma função para lerS/I/D diversas vezes

    //1. Sequencial ordenado
    
    //a) Gravar
    gravarS("seq.txt","5");
    gravarS("seq.txt","4");
    gravarS("seq.txt","3");
	gravarS("seq.txt","2");    
	gravarS("seq.txt","1");
    
	//b) Ler
	lerS("seq.txt", "2");

	//c) Modificar
	modificarS("seq.txt", "2", "200");

	//d)Excluir
	excluirS("seq.txt", "3");

    //2. Indexado
    //OBS: Utilizamos o padrão # #, para sinalizar que uma linha está vazia

    //a) Gravar
    gravarI("ind.txt","5");
    gravarI("ind.txt","4");
    gravarI("ind.txt","3");
	gravarI("ind.txt","2");    
	gravarI("ind.txt","1");
    
	//b) Ler
	lerI("ind.txt", "2");

	//c) Modificar
	modificarI("ind.txt", "2", "200");

	//d)Excluir
	excluirI("ind.txt", "3");
    
    //3. Direto

    //a) Gravar
    gravarD("dir.txt","5");
    gravarD("dir.txt","4");
    gravarD("dir.txt","3");
	gravarD("dir.txt","2");    
	gravarD("dir.txt","1");
    
	//b) Ler
	lerD("dir.txt", "2");

	//c) Modificar
	modificarD("dir.txt", "2", "200");

	//d)Excluir
	excluirD("dir.txt", "3");

    return 0;
}
