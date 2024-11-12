#ifndef BUSCA_H_INCLUDED
#define BUSCA_H_INCLUDED

// cabeçalhos
void TaxaAcertos(Contadores *contadores, Cache *memoria, int endereco, int PB, int NumConj, int NumLinhaConj, int resultado, int *MemoriaPCValores);
int EncontraLFULinha(Cache *memoria, int NumLinhaConj, int Conj);

void TransferirMPpCache(Cache *memoria, int NumLinha, int endereco, int PB, int *MemoriaPCValores) // transfere os valores da memoria principal para a cahce
{
    int Bloco, i; // indice e bits de bloco
    int PrimeiraPalavraBloco;
    Bloco = endereco / PB;             // bloco recebe o endereco sem as palavras
    PrimeiraPalavraBloco = Bloco * PB; // a primeira palavra recebe esses bits porem sem a tag
    for (i = 0; i < PB; i++)
    {
        memoria->MemoCache[NumLinha].palavra[i] = MemoriaPCValores[PrimeiraPalavraBloco]; // a palavra da memoria cache recebe o valor da mp
        PrimeiraPalavraBloco = PrimeiraPalavraBloco + 1;                                  // muda o indice da mp
    }
}
// funções
int BuscaCache(Cache *memoria, int endereco, int PB, int NumConj, int NumLinhaConj) // função para procurar a o endereço informado na cache
{
    int i, BuscTag, Conj, PrimeiraLinhaConj; // variaveis utilizadas
    int NumPalavra = endereco % PB;
    BuscTag = endereco / PB;     // mudar se eu divir o endereço pelo numero de palavras por bloco para assim tirar os bits porem não tendo ainda o valor da tag
    Conj = BuscTag % NumConj;    // o mod pega os bits mais a direita sem mover os bits em si
    BuscTag = BuscTag / NumConj; // busca tag pega os bits de maior valor do endereço

    PrimeiraLinhaConj = Conj * NumLinhaConj; // tira a tag do conjunto

    for (i = 0; i < NumLinhaConj; i++) // dentro do conjunto verifica se
    {
        if (memoria->MemoCache[PrimeiraLinhaConj].preenchido && memoria->MemoCache[PrimeiraLinhaConj].tag == BuscTag) // a memoria cache já está preenchida e sua tag já esta na busctag
        {
            memoria->MemoCache[PrimeiraLinhaConj].cont = memoria->MemoCache[PrimeiraLinhaConj].cont + 1; // se estiver aumenta 1 no contador LFU
            printf("%d", memoria->MemoCache[PrimeiraLinhaConj].palavra[NumPalavra]);                     // mostra a palavra
            return 1;
        }
        PrimeiraLinhaConj = PrimeiraLinhaConj + 1;
    }
    return -1;
}

int EncontraLFULinha(Cache *memoria, int NumLinhaConj, int Conj) // encontra linha para realizar o LFU
{
    int i;
    int linhaLFU;
    int PrimeiraLinhaConj;
    PrimeiraLinhaConj = Conj * NumLinhaConj;                      // pega o conjunto sem TAG e sem W
    int minContador = memoria->MemoCache[PrimeiraLinhaConj].cont; // os contadores começam iguais
    linhaLFU = PrimeiraLinhaConj;                                 // comeca com a 1° linha
    for (i = 1; i < NumLinhaConj; i++)
    {
        if (memoria->MemoCache[PrimeiraLinhaConj].cont < minContador) // se o contador for menor que o contador minimo
        {
            minContador = memoria->MemoCache[PrimeiraLinhaConj].cont; // o minimo contador recebe o valor do contador
            linhaLFU = PrimeiraLinhaConj;                             // a linha LFU recebe novamente a primeira linha do conjunto
            printf("linha lfu : %d", linhaLFU);                       // mostra a linha
        }
        PrimeiraLinhaConj = PrimeiraLinhaConj + 1; // incrementa no vetor
    }
    return linhaLFU; // retorna a linha encontrada
}

int EncontraLinhaVazia(Cache *memoria, int NumLinhaConj, int Conj)
{
    int i, PrimeiraLinhaConj;
    PrimeiraLinhaConj = Conj * NumLinhaConj; // pega o conjunto
    for (i = 0; i < NumLinhaConj; i++)
    {
        if (memoria->MemoCache[PrimeiraLinhaConj].preenchido == 0) // se ainda não foi preenchido retorna linha vazia
        {
            return PrimeiraLinhaConj;
        }
        PrimeiraLinhaConj = PrimeiraLinhaConj + 1; // incremento de vetor
    }
    return -1; // não foram encontradas linhas vazias
}

// Função para substituir uma linha na cache usando LFU
void SubstituiLinha(Cache *memoria, int NumLinhaConj, int Conj, int endereco, int PB, int *MemoriaPCValores)
{
    int linhaEscolhida;
    linhaEscolhida = EncontraLinhaVazia(memoria, NumLinhaConj, Conj); // procura linha vazia caso não ache
    if (linhaEscolhida == -1)
    {
        linhaEscolhida = EncontraLFULinha(memoria, NumLinhaConj, Conj); // procura uma linha para utilizar o LFU
    }

    int NumPalavra;
    NumPalavra = endereco % PB;
    memoria->MemoCache[linhaEscolhida].TamanhoW = log2(NumLinhaConj);
    memoria->MemoCache[linhaEscolhida].ConjD = Conj;
    memoria->MemoCache[linhaEscolhida].BlocS = endereco / PB;
    memoria->MemoCache[linhaEscolhida].tag = endereco / (PB * NumLinhaConj);
    memoria->MemoCache[linhaEscolhida].preenchido = 1;
    memoria->MemoCache[linhaEscolhida].cont = 1;
    TransferirMPpCache(memoria, linhaEscolhida, endereco, PB, MemoriaPCValores);

    printf("\nPalavra localizado %d", memoria->MemoCache[linhaEscolhida].palavra[NumPalavra]); // mostra a palavra
}

void TaxaAcertos(Contadores *contadores, Cache *memoria, int endereco, int PB, int NumConj, int NumLinhaConj, int resultado, int *MemoriaPCValores)
{
    int Conj, BuscTag;
    BuscTag = endereco / PB;     // pega o endereço sem o W
    Conj = BuscTag % NumConj;    // pega o conjunto sem a tag
    BuscTag = BuscTag / NumConj; // pega a tag

    if (resultado == -1) // se o não foi encontrado na cache incrementa 1 para a consuta
    {
        printf("\nPalavra nao encontrada na cache, Realizando troca.\n");
        Sleep(1000);
        printf("\nPalavra nao encontrada na cache, Realizando troca..\n");
        Sleep(1000);
        printf("\nPalavra nao encontrada na cache, Realizando troca...\n");
        Sleep(1000);
        SubstituiLinha(memoria, NumLinhaConj, Conj, endereco, PB, MemoriaPCValores);
        contadores->totalConsultas += 1;
    }
    else // se a palavra foi encontrada na cache incrementa 1 tanto para a consulta quanto para os acertos
    {
        contadores->totalAcertos += 1;
        contadores->totalConsultas += 1;
    }
}
#endif