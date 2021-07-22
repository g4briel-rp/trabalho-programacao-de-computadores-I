#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#define NUM_PALAVRAS 50

void imprimirForca(int erros){

    printf("  ______       \n");
    printf(" |/     |      \n");
    printf(" |    %c%c%c%c \n", (erros>=1?'|':' '), (erros>=2?'*':' '), (erros>=3?'*':' '), (erros>=4?'|':' '));
    printf(" |    %c%c%c%c \n", (erros>=5?'|':' '), (erros>=6?'_':' '), (erros>=7?'_':' '), (erros>=8?'|':' '));
    printf(" |    %c%c%c   \n", (erros>=9?'-':' '), (erros>=10?'|':' '), (erros>=11?'-': ' '));
    printf(" |     %c      \n", (erros>=12?'|':' '));
    printf(" |    %c %c    \n", (erros>=13?'/':' '), (erros>=14?'\\':' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");
}

void ganhou(){

    printf("\t  O\n");
    printf("\t \\|/\n");
    printf("\t  |\n");
    printf("\t / \\\n");
}

void perdeu(){

    printf("\t _______\n");
    printf("\t| x   x |\n");
    printf("\t|   ^   |\n");
    printf("\t|  xxx  |\n");
}

void ordenar(int k,char usadas[]){

    int i,j;
    char ord;

    for(j=0;j<k;j++){
        for(i=j;i<k;i++){
            if(usadas[j]>usadas[i]){
                ord=usadas[j];
                usadas[j]=usadas[i];
                usadas[i]=ord;
            }
        }
    }

    letrasUsadas(k,usadas);
}

void letrasUsadas(int k,char usadas[]){

    int j;

    for(j=0;j<k;j++){
        printf(" %c ",usadas[j]);
        if(j!=(k-1)){
            printf("-");
        }
    }
}

void imprimirPalavra(int numero,int tam[],char letra[]){

    int j;

    for(j=0;j<tam[numero];j++){
        printf("%c ",letra[j]);
    }
}

int confere(char chute, char mat[][20],int tam[],int numero){

    int x;

    for(x=0;x<tam[numero];x++){
        if(chute==mat[numero][x]){
            return 1;
        }
    }

    return 0;
}

int main()
{
    setlocale(LC_ALL,"");

    int i=0,j=0,jogar=0,tam[NUM_PALAVRAS],acerto=0,erros=0,k=0,escolha;
    char mat[NUM_PALAVRAS][20],aux[20],chute,letra[50],saida,usadas[50];

    FILE *port;
    FILE *ing;

    port=fopen("port.txt","r");

    if (port == NULL){
        return EXIT_FAILURE;
    }

    ing=fopen("ing.txt","r");

    if (ing == NULL){
        return EXIT_FAILURE;
    }

    printf("\tSEJA BEM VINDO AO JOGO DA FORCA !!!!\n\n");

    printf("**********************REGRAS**************************\n");
    printf("*** -Voce tem 15 tentativas para acertar a palavra ***\n");
    printf("*** -Idioma so pode ser escolhido uma vez          ***\n");
    printf("*** -Apenas uma letra por tentativa                ***\n");
    printf("******************************************************\n\n");

    printf("1-Portugues\n");
    printf("2-Ingles\n");
    printf("ESCOLHA O IDIOMA: \nR: ");
    scanf("%d",&escolha);

    printf("\n");

    system("pause");

    while(jogar==0){

        system("cls");

        rewind(port);
        rewind(ing);

        srand(time(NULL));

        int numero=rand()%NUM_PALAVRAS;

        if(escolha==1){
            for(j = 0; j < NUM_PALAVRAS; j++){
                fscanf(port, "%s", aux);
                tam[j] = strlen(aux);
                for (i = 0; i < tam[j]; i++){
                    mat[j][i] = aux[i];
                }
            }
        }else if(escolha==2){
                for(j = 0; j < NUM_PALAVRAS; j++){
                    fscanf(ing, "%s", aux);
                    tam[j] = strlen(aux);
                    for (i = 0; i < tam[j]; i++){
                        mat[j][i] = aux[i];
                    }
                }
        }else{

            printf("OPCAO INVALIDA !!\nREINICIE O JOGO !!\n");
            return 0;
        }

        printf("PALAVRA - >  ");

        for(j=0;j<50;j++){
            letra[j]='_';
            usadas[j]='_';
            if(j<tam[numero]){
                printf("%c ",letra[j]);
            }
        }

        printf("\n\n");

        i=0;

        do{
            imprimirForca(erros);

            if(erros==14){
                printf("*** ULTIMA TENTATIVA ***\n\n");
            }

            printf("TENTATIVAS: %d\n\n",erros);

            fflush(stdin);
            printf("Digite uma letra(minuscula): ");
            scanf("%c",&chute);

            system("cls");

            if(chute>='a' && chute<='z'){

                int usou=0;

                for(j=0;j<=k;j++){
                    if(chute==usadas[j]){
                        usou++;
                    }
                }

                if(usou==0){
                    usadas[k]=chute;
                    k++;
                    if(confere(chute,mat,tam,numero)==1){
                        printf("A letra '%c' esta na palavra\n\n",chute);
                    }else{
                        printf("Que pena, tente novamente\n\n");
                        erros++;
                    }

                    printf("PALAVRA - >  ");

                    for(j=0;j<tam[numero];j++){
                        if(chute==mat[numero][j]){
                            letra[j]=chute;
                            printf("%c ",letra[j]);
                            acerto++;
                        }else{
                            printf("%c ",letra[j]);
                        }
                    }

                    printf("\n\n");

                    printf("Letras usadas: ");

                    ordenar(k,usadas);

                    printf("\n\n");

                }else{
                    printf("LETRA REPETIDA !!!!\n\n");

                    printf("PALAVRA - >  ");

                    imprimirPalavra(numero,tam,letra);

                    printf("\n\n");

                    printf("Letras usadas: ");

                    ordenar(k,usadas);

                    printf("\n\n");
                }
            }else{
                printf("CARACTER INVALIDO !!!!\n\n");

                printf("PALAVRA - >  ");

                imprimirPalavra(numero,tam,letra);

                printf("\n\n");

                printf("Letras usadas: ");

                ordenar(k,usadas);

                printf("\n\n");
            }

            }while(acerto!=tam[numero] && erros<15);

            system("cls");

            if(acerto==tam[numero]){
                printf("A palavra era: ");

                for(i=0;i<tam[numero];i++){
                    printf("%c ",mat[numero][i]);
                }

                printf("\n\nPARABENS VOCE ACERTOU A PALAVRA ANTES DE SER ENFORCADO !!\n\n");

                ganhou();

            }else{
                printf("A palavra era: ");

                for(i=0;i<tam[numero];i++){
                    printf("%c ",mat[numero][i]);
                }

                printf("\n\nE MORREU !!\n\n");

                perdeu();
            }

            printf("\n\nErros: %d - > ",erros);
            if(erros==0){
                printf("MUITO BOM");
            }else if(erros>=1 && erros<=4){
                printf("BOM");
            }else if(erros>=5 && erros<=8){
                printf("REGULAR");
            }else if(erros>8 && erros<=11){
                printf("RUIM");
            }else if(erros>12){
                printf("PRECISA PRATICAR MAIS !!!");
            }

            printf("\n\nLetras usadas: ");

            ordenar(k,usadas);

            printf("\n");

            fflush(stdin);

            printf("\n\nJOGAR NOVAMENTE ? (S/N)\nR: ");

            scanf("%c",&saida);

            if(saida=='S'||saida=='s'){
                erros=0;
                acerto=0;
                k=0;
            }else if(saida=='N'||saida=='n'){
                jogar=1;
            }
    }

    fclose(port);
    fclose(ing);

    return 0;
}
