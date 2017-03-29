#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double pesos[3];
double limite=0.2;


int Saida(int entrada[3]){
	double soma = 0.0;
	int i;
	
	for(i=0;i<3;i++){
		soma+=pesos[i]*entrada[i];
	}
	
	
	if(soma>limite) return 1;
	
	return -1;
	
}


void treinar(int entrada[4][3], int target[4], double lmt, double taxa, int epoca){
	
	limite=lmt;
	int i,j,k,soma;
	
	for(i=0;i<3;i++){
		pesos[i]=rand();
	}
	
	for(i=0;i<epoca;i++){
		int erroTotal = 0;
		for(j=0;j<4;j++){
			
			int saida = Saida(entrada[j]);
			int erro = target[j] - saida;
			
			erroTotal+=erro;
			
			for(k=0;k<3;k++){
				double delta = taxa * entrada[j][k] * erro;
				pesos[k]+=delta;
				
			}
			
			
		}
		
		if(erroTotal==0) break;
	}
}

int main(){
	srand(time(NULL));
	int entrada[4][3]={{1,1,1},{1,1,0},{1,0,1},{0,1,1}};
	int target[4]={1,-1,-1,-1};
	int resposta;
	
	treinar(entrada,target,0.2,0.1,999999999);
	
	resposta=Saida(entrada[0]);
	printf("esperado 1 deu %d\n", resposta);
	
	resposta=Saida(entrada[1]);
	printf("esperado -1 deu %d\n", resposta);
	
	resposta=Saida(entrada[2]);
	printf("esperado -1 deu %d\n", resposta);
	
	resposta=Saida(entrada[3]);
	printf("esperado -1 deu %d\n", resposta);
	
}