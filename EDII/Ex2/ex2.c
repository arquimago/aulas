#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int lista1 = {26,76,39,61,25,10,16,70,53}; //9 elementos
int lista2 = {967,875,985,214,357,248,137,864,247,135}; //10 elementos

int hash1(int num){
	int hash = 0;
	hash=num%7;
	return hash;
}

int desloc1(int num){
	int hash = 0;
	hash=(num%2)+1;
	return hash;
}

int hash2(int num){
	int hash = 0;
	hash=num%11;
	return hash;
}

int desloc2(int num){
	int hash = 0;
	hash=(num%2)+1;
	return hash;
}

int hash3(int num){
	int hash = 0;
	hash=num%13;
	return hash;
}

int desloc3(int num){
	int hash = 0;
	hash=(num%4)+1;
	return hash;
}

int hash4(int num){
	int hash = 0;
	hash=num%17;
	return hash;
}

int desloc4(int num){
	int hash = 0;
	hash=(num%3)+1;
	return hash;
}

int main(){
	printf("Lista de Exercícios - Parte 2\n");
	printf("Exercício 1\n");
	printf("letra a)\n");
	
	printf("letra b)\n");
	
	printf("\nExercício 2\n");
	printf("letra a)\n");
	
	printf("letra b)\n");
	
	printf("\nExercício 3\n");
	printf("letra a)\n");
	
	printf("letra b)\n");
	
	printf("\nExercício 4\n");
	printf("letra a)\n");
	
	printf("letra b)\n");
	
	return 0;
}

