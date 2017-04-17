#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Esta função abre o arquivo com ponteiro no final dele
Se o arquivo não existir ele cria o arquivo
usando o padrão de 4 digitos para o nome, lembrando que
padronizamos 4 digitos para a chave do post e os outros 4
para chave da resposta.

Ex. 12340020 gera o arquivo 1234.txt e o registro 0020
 lá dentro do arquivo é o código que a gente quer (tratando fora da função)
*/
FILE* abreArquivo(int codigo){
	char nome[8];
	FILE* retorno;
	if(codigo>99999999||codigo<0) {
		printf("Nome Errado!\n");
		return NULL;
	} else {
		int cod4 = codigo/10000;
		sprintf(nome,"%d",cod4);
		if(cod4<10){
			nome[3]=nome[0];
			nome[2]='0';
			nome[1]='0';
			nome[0]='0';
		} else if(cod4<100){
			nome[3]=nome[1];
			nome[2]=nome[0];
			nome[1]='0';
			nome[0]='0';
		} else if(cod4<1000){
			nome[3]=nome[2];
			nome[2]=nome[1];
			nome[1]=nome[0];
			nome[0]='0';
		}
		nome[4]='\0';
	}
	strcat(nome, ".txt");
	retorno = fopen (nome,"a");
	return retorno;
}

int main(){
	FILE *teste;
	teste = abreArquivo(12340000);
	fputs("teste",teste);
	fclose(teste);
	return;
}