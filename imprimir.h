#ifndef IMPRIMIR_H_INCLUDED
#define IMPRIMIR_H_INCLUDED

void imprimir(Contadores contadores) // função para imprimir
{
    float porAcertos;
    porAcertos = contadores.totalAcertos / (float)contadores.totalConsultas; // calcula a % em decimal (ex 3,22200)
    printf("---------------------------------\n");
    printf("|Alunos:\t\t\t|\n"); // nome de quem fez o trabalho
    printf("|Guilherme Vilches\t\t|\n");
    printf("|Lucas Leite Lima\t\t|\n");
    printf("---------------------------------\n");
    printf("Total de consutas : (%d)\n", contadores.totalConsultas); // numero total de consutas
    printf("porcentagem de acertos : (%.2f)\n", porAcertos * 100);   // porcentagem com duas casas decimais
}

void mostra_cache(Cache memoria, int TamCache, int *MemoriaPCValores) // mostra os valores da memoria cache
{
    int i; // indice
    for (i = 0; i < TamCache; i = i+4)
    {
        if (memoria.MemoCache[i].preenchido == 1 && memoria.MemoCache[i].cont > 0) // se o vetor cache esta preenchido e tem contador > 0 ou seja foi acessado essa memoria
        {
            printf("\n\nendereco (%d) : %d e acessado (%d)\n", i/4, MemoriaPCValores[i], memoria.MemoCache[i].cont); // mostre tag, d, w ,s, o endereço e a quantidade de acessos
            printf("\nnumero de bits em W = (%d)\n(D) Conj atual = (%d)\nbits de (S) = (%d)\nTAG = (%d)\n",memoria.MemoCache[i].TamanhoW,memoria.MemoCache[i].ConjD,memoria.MemoCache[i].BlocS,memoria.MemoCache[i].tag);
        }
        else // se não informe que está vazio
        {
            printf("\nendereco (%d) : NULL\n", i/4);
        }
    }
    system("PAUSE"); // pausa
}
#endif