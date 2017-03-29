#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define LEARNING_RATE    1.0
#define MAX_ITERATION    1000
#define EXEMPLOS 21

double peso[7][7][9];
double bias[7];

double randomFloat(){
    return (double)rand() / (double)RAND_MAX;
}

void calculaSaida(int entrada[][], int saida[]){
    int i,j,k;
	double soma;
	
	for(i=0;i<7;i++){
		soma=0.0;
		for(j=0;j<7;j++){
			for(k=0;k<9;k++){
				soma+=entrada[j][k]*peso[i][j][k];
			}
		}
		soma+=bias[i];
		if(soma>=0) saida[i] = 1;
		else saida[i] = 0;
	}
}

void letraTarget(char letra, int *target){
	switch(letra){
		case 'a':
			target[0]=1;
			break;
		case 'b':
			target[1]=1;
			break;
		case 'c':
			target[2]=1;
			break;
		case 'd':
			target[3]=1;
			break;
		case 'e':
			target[4]=1;
			break;
		case 'j':
			target[5]=1;
			break;
		case 'k':
			target[6]=1;
			break;
		default:
			printf("ERRO!\n");
			break;
	}
}

void targetLetra(int *target){
	int i;
	for(i=0;i<7;i++){
		if(!target[i])
			printf(". ");
		else {
			switch(i){
				case 0:
					printf("a ");
					break;
				case 1:
					printf("b ");
					break;
				case 2:
					printf("c ");
					break;
				case 3:
					printf("d ");
					break;
				case 4:
					printf("e ");
					break;
				case 5:
					printf("j ");
					break;
				case 6:
					printf("k ");
					break;
				default:
					printf("ERRO!\n");
					break;
			}
		}
	}
	printf("\n");
}


int main(int argc, char* argv[]){
	srand(time(NULL));
	int entrada[EXEMPLOS][7][9];
	int target[EXEMPLOS][7];
	int teste[7][9];
	int saida[7];
	int i,j,k,epoca;
	char letra;	
	double erroLocal, erroGlobal;
	//captura entrada de treinamento
	FILE* input = fopen(argv[1], "r");
	if(input==NULL){
		printf("Falha no acesso ao arquivo de treinamento");
		exit(42);
	}
	memset(target,0,sizeof(target));
	for(i=0;i<EXEMPLOS;i++){
		fscanf(input,"%c",&letra);
		letraTarget(letra,&target[i]);
		for(j=0;j<7;j++){
			for(k=0;k<9;k++){
				fscanf(input,"%d",entrada[i][j][k]);
			}
		}
	}
	//inicia pesos aleatórios
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			for(k=0;k<9;k++){
				peso[i][j][k] = randomFloat();
			}
		}
	}
	//treina a rede
	epoca=0;
	do{
		epoca++;
		erroGlobal=0;
		
	}while(globalError != 0 && epoca<=MAX_ITERATION);

	//testa a rede
	fclose(input);
	input = fopen(argv[2], "r");
	if(input==NULL){
		printf("Falha no acesso ao arquivo de testes");
		exit(51);
	}
	while(fscanf(input,"%c",&letra)!=EOF){
		for(i=0;i<7;i++){
			for(j=0;j<9;j++){
				fscanf(input,"%d",teste[i][j]);
			}
		}
		calculaSaida(teste,saida);
		printf("Para o teste %d resultado: ", i);
		targetLetra(saida);
	}
	fclose(input);
	return 0;
}