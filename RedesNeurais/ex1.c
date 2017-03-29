#include <stdio.h>
#include <stdlib.h>

#define LEARNING_RATE    0.1
#define MAX_ITERATION    100
#define THETA            0.1

int calculateOutput(float weights[], float x, float y, float z){
	int resultado;
	float sum = x * weights[0] + y * weights[1] + z * weights[2] + weights[3];
	if(sum>THETA) resultado = 1;
	else if(sum<-(THETA)) resultado = -1;
	else resultado = 0;
	
	return resultado;
}

int main() {
	srand(time(NULL));
	float localError, globalError;
	int patternCount, i, p, iteration, output;
	float x[4] = {1.0,1.0,1.0,0.0};
	float y[4] = {1.0,1.0,0.0,1.0};
	float z[4] = {1.0,0.0,1.0,1.0};
	int outputs[4] = {1,-1,-1,-1};
	float weights[4] = {0.0,0.0,0.0,0.0};
	
	patternCount = 4;
	iteration = 0;
	do {
		iteration++;
		globalError = 0;
		
		for (p = 0; p < patternCount; p++) {
			output = calculateOutput(weights, x[p], y[p], z[p]);
			localError = outputs[p] - output;
		
			weights[0] += LEARNING_RATE * localError * x[p];
			weights[1] += LEARNING_RATE * localError * y[p];
			weights[2] += LEARNING_RATE * localError * z[p];
			weights[3] += LEARNING_RATE * localError;

			globalError += (localError*localError);
		}

		printf("Pesos para a epoca %d: w1=%.2f w2=%.2f w3=%.2f bias=%.2f\n", iteration, weights[0], weights[1], weights[2], weights[3]);
		   
	} while (globalError != 0 && iteration<=MAX_ITERATION);

	printf("\nEquacao final: %.2f*x1 + %.2f*x2 %.2f*x3  + %.2f = 0\n", weights[0], weights[1], weights[2], weights[3]);

	return 0;
}
