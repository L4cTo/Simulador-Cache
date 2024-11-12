#ifndef REESCREVER_H_INCLUDED
#define REESCREVER_H_INCLUDED

typedef struct Reescrita // para reescrever de forma eficiente no arquivo tive que implementar essa estrutura
{
    int MP; // Memoria Principal
    int PB; // Palavras por Bloco
    int TC; // Tamanho da Cache
    int NC; // Numero de Conjuntos
} Rescreita; // novo nome

void reescreve_arquivo(char *pasta) // recebe o vetor para confirmar o arquivo
{
    Rescreita R; // inicialização da estrutura
    system("cls"); // limpa o codigo

    printf("\ninforme o nome do arquivo (caso nao exista, essa funcao cria um arquivo com o nome inserido\n[PRECISA ter .txt])\n"); // informações basicas

    scanf("%s", pasta);              // recebe o texto escrito
    FILE *file = fopen(pasta, "wb"); // inicializa o arquivo

    if (file) // não é necessario um else por conta da função criar um arquivo caso o anterior não exista
    {
        printf("informe o valor da Memoria Principal(kb)\n"); // guarda os valores da memoria principal
        scanf("%d", &R.MP);
        printf("informe a quantidade de Palavras por Bloco(bits)\n"); // guarda os valores da quantidade de palavra por bloco
        scanf("%d", &R.PB);
        printf("informe o Tamanho da Cache(kb)\n"); // guarda os valores do tamanho da memoria cache
        scanf("%d", &R.TC);
        printf("informe o valor da Numero de Conjuntos(bits)\n"); // guarda os valores do numero do conjunto de bits
        scanf("%d", &R.NC);
        fprintf(file, "%d\n%d\n%d\n%d", R.MP, R.PB, R.TC, R.NC); // e os coloca no arquivo
        fclose(file);
        printf("arquivo reescrito com sucesso!!"); // informa que foi reescrito / escrito
        system("PAUSE");
    }
}

#endif