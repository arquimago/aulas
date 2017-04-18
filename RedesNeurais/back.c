#include <stdlib.h>
#include <stdio.h>
#include <math.h>

const int numEpocas = 500000;
const double alpha = 0.2;

int padraoNum = 0;
double erroDestePadrao = 0.0;
double saidaPredita = 0.0;
double erroQuad = 0.0;

double valoresOcultos[5];

double pesosInputOcultos[3][4] = {{0.3099,0.1904,-0.0347,-0.4861},{0.1970,0.3191,-0.1448,0.3594},{-0.3378,0.2771,0.2859,-0.3329}};
double pesosOcultosSaida[5]={0.3581,-0.3979,-0.2913,0.4919,-0.1401};

int treinoEntrada[4][3];
int treinoSaida[4];

double binary_sigmoid(double x){
	return(1.0 / (1.0 + exp(-x)));
}

double binary_sigmoid_dev(double x){
    return binary_sigmoid(x) *
    ( 1 - binary_sigmoid(x));
}


double bipolar_sigmoid(double x){
    return (2.0 / (1.0 + exp(-x))) - 1;
}

double bipolar_sigmoid_dev(double x){
    return (1.0/2.0) *
    (1.0 + bipolar_sigmoid(x))
    * ( 1 - bipolar_sigmoid(x));
}


void calcNet(){
    int i,j;
    for(i=0;i<4;i++){
	  valoresOcultos[i] = 0.0;

        for(j=0;j<3;j++){
			valoresOcultos[i] += (treinoEntrada[padraoNum][j] * pesosInputOcultos[j][i]);
        }
		valoresOcultos[i] = bipolar_sigmoid(valoresOcultos[i]);
		//valoresOcultos[i] = binary_sigmoid(valoresOcultos[i]);
    }
	
	valoresOcultos[4] = 1.0;
	saidaPredita = 0.0;
	for(i=0;i<5;i++){
		saidaPredita+=(valoresOcultos[i] * pesosOcultosSaida[i]);
	}
    erroDestePadrao = saidaPredita - treinoSaida[padraoNum];
}


void AjustaPesosOcultosSaida(){
	int k;
	for(k=0;k<5;k++){
		double mudancaDePeso = alpha * erroDestePadrao * valoresOcultos[k];
		pesosOcultosSaida[k] = pesosOcultosSaida[k] - mudancaDePeso;
		if (pesosOcultosSaida[k] < -5){
			pesosOcultosSaida[k] = -5;
		}else if (pesosOcultosSaida[k] > 5){
			pesosOcultosSaida[k] = 5;
		}
   }
}


void AjustaPesosEntradaOcultos(){
	int i,k;
	for(i=0;i<4;i++){
		for(k=0;k<3;k++){
		double x = 1 - (valoresOcultos[i] * valoresOcultos[i]);
		x = x * pesosOcultosSaida[i] * erroDestePadrao * alpha;
		x = x * treinoEntrada[padraoNum][k];
		double mudancaDePeso = x;
		pesosInputOcultos[k][i] = pesosInputOcultos[k][i] - mudancaDePeso;
		}
	}

}


void inicializar(){
    printf("Inicializando Entrada\n");

    treinoEntrada[0][0]  = 1;
    //treinoEntrada[0][1]  = 0;
	treinoEntrada[0][1]  = -1;
    treinoEntrada[0][2]  = 1;    //bias
    treinoSaida[0] = 1;

    //treinoEntrada[1][0]  = 0;
	treinoEntrada[1][0]  = -1;
    treinoEntrada[1][1]  = 1;
    treinoEntrada[1][2]  = 1;       //bias
    treinoSaida[1] = 1;

    treinoEntrada[2][0]  = 1;
    treinoEntrada[2][1]  = 1;
    treinoEntrada[2][2]  = 1;        //bias
    //treinoSaida[2] = 0;
	treinoSaida[2] = -1;

    //treinoEntrada[3][0]  = 0;
    treinoEntrada[3][0]  = -1;
    //treinoEntrada[3][1]  = 0;
	treinoEntrada[3][1]  = -1;
	treinoEntrada[3][2]  = 1;     //bias
    //treinoSaida[3] = 0;
	treinoSaida[3] = -1;

}


void imprimeResultado(){
	int i;
	for(i=0;i<4;i++){
		padraoNum = i;
		calcNet();
		printf("padrao = %d real = %d modelo = %f\n",padraoNum+1,treinoSaida[padraoNum],saidaPredita);
	}
}

void calculaErroQuad(){
    erroQuad = 0.0;
    int i;
	for(i=0;i<4;i++){
        padraoNum = i;
        calcNet();
        erroQuad = erroQuad + (erroDestePadrao * erroDestePadrao);
    }
    //erroQuad = erroQuad/4;
    //erroQuad = sqrt(erroQuad);
}

int main(){
	int i,j;
	inicializar();
    for(i=0;i<= numEpocas;i++){
        for(j=0;j<4;j++){
            padraoNum = j;
			calcNet();
			AjustaPesosOcultosSaida();
			AjustaPesosEntradaOcultos();
        }
        calculaErroQuad();
        printf("Epoca = %d Erro Quadratico = %f\n",i,erroQuad);
		if(erroQuad<=0.05) break;
    }
	imprimeResultado();
	system("PAUSE");
	return 0;
}
