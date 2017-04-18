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
	//controladores do sistema
	int maiorchavepost = 0; // carregar do arquivo que diz a maior chave de post ja adicionada
	int maiorchaveresp = 0; // carregar do arquivo que diz a maior chave de resposta ja adicionada
	int postsetado = 0; // setar quando o ususario selecionar um post no submenu
	int respostasetada = 0; // setar quando o usuario escolher uma resposta no submenu
	//////////////////////////
	int opcao;
	int opcao2;
	int opcao3;
	while(1){
		do{
			system("cls");
			printf("\n-----------------Forum--------------\n");
			printf("1 - Ver Posts\n");
			printf("2 - Postar\n");
			printf("3 - Pesquisar\n");
			printf("4 - Sair\n");
			printf("\n------------------------------------\n");
			scanf("%d", &opcao);
			if(opcao == 4){//Sair
				return 0;
			}
		}while(opcao != 1 && opcao != 2 && opcao != 3);
    if(opcao == 1){//Ver Posts

        do{
            system("cls");
            printf("\n--------Lista de Posts----------\n");
            // LISTARPOSTS()
                //chave1 - msg
                //chave2 - msg
            // SETARPOST() setar como post escolhido o de chave1 ou de chave2
            printf("\n------Informações do Post--------\n");
            printf("1 - Respostas Posts\n");
            printf("2 - Apagar Post\n");
            printf("3 - Voltar\n");
            printf("\n---------------------------------\n");
            scanf("%d", &opcao2);
        }while(opcao2 != 1 && opcao2 != 2 && opcao2 != 3);
        if(opcao2 == 1){// Respostas

                do{
                    system("cls");
                    printf("\n------Respostas--------\n");
                    printf("1 - Responder\n");
                    printf("2 - Apagar Resposta\n");
                    printf("3 - Voltar\n");
                    scanf("%d", &opcao3);
                }while(opcao3 != 1 && opcao3 != 2 && opcao3 != 3);
                if(opcao3 == 1){

                }else if(opcao3 == 2){
                    // LISTARRESPOSTAS()
                        //chave1 - msg
                        //chave2 - msg
                    // SETARRESPOSTA() setar como resposta escolhida a de chave1 ou de chave2 e imediatamente "deletar"
                }else{

                }

        }else if(opcao2 == 2){

        }else{
        }
    }else if(opcao == 2){//Postar
            FILE *teste;
            maiorchavepost = maiorchavepost+1;
            teste = abreArquivo(maiorchavepost);
            //teste = abreResposta3(12345678);
            char msg[31];
            scanf("%s", msg);
            fputs(msg,teste);
            fclose(teste);
    }else{//Pesquisar

    }
	}



        //system("pause");


        //postarResposta(1234,5678,"Ola pessoas o//");
        return;
}