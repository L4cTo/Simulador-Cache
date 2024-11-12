
//Alunos : Guilherme Vilches, Lucas Leite

// Bibliotecas
#include <stdio.h>      //usado para abrir os files
#include <stdlib.h>     //usado para as funções basicas do c
#include <conio.h>      //mudar a cor de alguns caracteres
#include <time.h>       //usado para o Sleep
#include <windows.h>    //usado para fazer a alteração de cores
#include <math.h>       //usado na função busca
#include <string.h>     //usado para comparar se o arquivo informado é realmente o .txt
#include "menu.h"       //cria o menu
#include "file.h"       //realiza o armazenamento de dados do file e cria a cache
#include "busca.h"      //realiza a busca na memoria cache
#include "imprimir.h"   //mostra a taxa de acertos, memoria cache e a memoria principal
#include "reescrever.h" //limpa e modifica os valores do arquivo

// inicializa o emulador

int main()
{
    int compara, retorno, end, MemPrinc, PalavraBloc, TamCache, NumeLinhaConj, TamLinhas, Conj, *MemoriaPCValores = 0, terminalaco = 0;
    Cache memoria;  // inicializa a estrutura para a cache
    char pasta[10]; // vetor para confirmar se o arquivo está correto

    Contadores contadores;       // inicializa a estrutura para a taxa
    contadores.totalAcertos = 0; // inicia seus valores
    contadores.totalConsultas = 0;

    retorno = menu(); // inicializa o menu
    do
    {
        switch (retorno) // escolhe
        {
        case 1: // caso 1 pega o arquivo .txt e utiliza seus dados
            system("cls");
            printf("\ninforme o arquivo a ser lido (necessesario colocar o [.txt])\n");
            scanf("%s", pasta);
            do // laço para ver se o arquivo inserido foi o arquivo .txt correto
            {
                if (compara == 0) // atraves de manipulação de string para ver se o arquivo é o correto
                {
                    LerF(&MemPrinc, &PalavraBloc, &TamCache, &NumeLinhaConj, &MemoriaPCValores,pasta);
                    TamLinhas = TamCache * 1024 / PalavraBloc * 4;
                    Conj = TamLinhas / NumeLinhaConj;
                    criaCache(&memoria, TamCache, PalavraBloc, TamLinhas);
                }
                else // caso esteja errado
                {
                    printf("\nentre com arquivos validos\n");
                    scanf("%s", pasta);
                    compara = strcmp(pasta, "entrada");
                }

            } while (compara != 0); // termino do laço

            retorno = menu(); // volta para o menu
            break;
        case 2: // caso 2 busca na memoria cache o arquivo da memoria principal
            system("cls");
            do
            {

                printf("informe o endereco desejado\n se Palavras por Bloco for :\n\n\n(LEMBRE que dependendo do tamanho da cache e da \nquantidade de palavras por bloco pode-se ter um valor maximo)\n\n");
                scanf("%d", &end);
                if (end >= 0 && end <= MemPrinc / 4) // se o valor inserido como "end" de "endereço" for possitivo de 0 até a memoria principal /4
                {
                    int resultado;
                    resultado = BuscaCache(&memoria, end, PalavraBloc, Conj, NumeLinhaConj);                                // pega o resultado da busca na cache se achou retorna 1 se não retorna -1
                    TaxaAcertos(&contadores, &memoria, end, PalavraBloc, Conj, NumeLinhaConj, resultado, MemoriaPCValores); // retorna a qauntidade de acertos / pela quantidade de processos
                }
                else
                {
                    printf("\ninforme um endereço valido!!\n");
                }
                printf("\n\n");

                printf("deseja continuar? (1 = sim, 2 = nao)");
                scanf("%d", &terminalaco);
                system("cls");

            } while (terminalaco != 2); // basicamente te prende em um laço até voce desejar sair e parar de inserir endereços para a cache

            system("PAUSE");
            retorno = menu(); // volta para o menu
            break;
        case 3: // caso 3 mostra a memoria cache e a taxa de acertos
            system("cls");
            imprimir(contadores);
            mostra_cache(memoria, TamCache, MemoriaPCValores);
            retorno = menu();
            break;
        case 4: // caso 4 modifica o arquivo inserido sem precisar fechar o terminal
            system("cls");
            reescreve_arquivo(pasta);
            retorno = menu();
            break;
        default:
            return 0; // caso seja encontrado algum erro, ou seja digitado um valor extremamente invalido
            break;
        }
    } while (retorno != 0); // termina o codigo
}
