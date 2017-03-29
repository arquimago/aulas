#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
	char palavra[40];
	int x,i;
	while(1){
		scanf("%s", palavra);
		x = strlen(palavra);
		for(i=0;i<x;i++){
			switch(palavra[i]){
				case 'a':
					printf("00000");
					break;
				case 'c':
					printf("00001");
					break;
				case 'd':
					printf("00010");
					break;
				case 'e':
					printf("00011");
					break;
				case 'h':
					printf("00100");
					break;
				case 'i':
					printf("00101");
					break;
				case 'l':
					printf("00110");
					break;
				case 'm':
					printf("00111");
					break;
				case 'n':
					printf("01000");
					break;
				case 'o':
					printf("01001");
					break;
				case 'p':
					printf("01010");
					break;
				case 'q':
					printf("01011");
					break;
				case 'r':
					printf("01100");
					break;
				case 's':
					printf("01101");
					break;
				case 't':
					printf("01110");
					break;
				case 'u':
					printf("01111");
					break;
				case 'v':
					printf("10000");
					break;
				default:
					printf("ERRO");
			}
		}
		
		printf("\n");
	}
	return 0;
}