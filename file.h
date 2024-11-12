#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

// structs
typedef struct linha
{
    int cont;       // contador
    int preenchido; // confirma espaço
    int *palavra;   // armazena a palavra que esta no W
    int tag;        // armazena a quantidade de bits mais significativos
    int BlocS;      // armazena a quantidade de bits utilizados no conjunto da memoria principal
    int ConjD;      // armazena a quantidade de bits utilizados no conjunto da memoria cache
    int TamanhoW;   // armazena a quantidade de bits utilizados na palavra/ menos significativos
} linha;

typedef struct // estrutura para a conta da taxa de acertos
{
    int totalAcertos;   // acertos na cache
    int totalConsultas; // total de consultas na cache
} Contadores;

typedef struct Cache
{
    linha *MemoCache; // cria um vetor para a memoria cache
} Cache;

// funções
void criaCache(Cache *memoria, int TamCache, int PB, int TamLinhas) // inicializa e malloca valores para a cache
{
    int i;
    memoria->MemoCache = (linha *)malloc(sizeof(linha) * TamLinhas); // cria um vetor para ser as linhas da cache
    if (memoria->MemoCache)
    {
        for (i = 0; i < TamCache; i++)
        {
            memoria->MemoCache[i].palavra = (int *)malloc(sizeof(int) * PB); // cria um vetor para ser as palavras na linha da cache
            memoria->MemoCache[i].preenchido = 0; // marca como vazio
        }
    }
    else // caso ocorra algum erro
    {
        printf("Erro ao alocar");
        free(memoria);
    }
}

void escreve_arquivo(int **MemoriaPCValores, int numeroPalavras) // mostra a mp em um arquivo .txt com suas respectivas palavras
{
    int i;
    FILE *file = fopen("ArquivoMemoria.txt", "wb"); // arquivo onde os dados da MP ficam
    if (file)
    {
        for (i = 0; i < numeroPalavras; i++)
        {
            fprintf(file, "%d -- %d\n", i, (*MemoriaPCValores)[i]); // mostra em si as palavras da mp e seu indice
        }
    }
    else
    {
        fclose(file);
    }
}

void zera_arquivo() // limpa o arquivo onde as palavras da MP estão para reutilizar sem problemas
{
    FILE *file = fopen("ArquivoMemoria.txt", "w");
    fclose(file);
}

void LerF(int *MemPrinc, int *PalavraBloc, int *TamCache, int *NumeLinhaConj, int **MemoriaPCValores, char *pasta)
{
    FILE *file = fopen(pasta,"rb"); // abre o arquivo .txt
    int MP, PB, TC, NC;                      // variaveis para receberem os valores do arquivo
    zera_arquivo();

    if (file) // verifica se o arquivo foi aberto corretamente
    {
        fscanf(file, "%d%d%d%d", &MP, &PB, &TC, &NC); // pega os valores do arquivo
    }
    else // caso dê algum erro na leitura do arquivo
    {
        printf("Erro!!");
        fclose(file);
    }

    *MemPrinc = MP;      // salva a Memoria Principal
    *PalavraBloc = PB;   // salva a quantidade de Palavras por Bloco
    *TamCache = TC;      // salva o Tamanho da Cache
    *NumeLinhaConj = NC; // salva o Numero de Linhas por Conjunto

    int numeroPalavras, i;
    *MemPrinc = *MemPrinc * 1024;                                    // transforma a MP de Kbits para bits
    numeroPalavras = *MemPrinc / 4;                                  // separa pelo conjunto
    *MemoriaPCValores = (int *)malloc(sizeof(int) * numeroPalavras); // aloca um vetor para ser a mp com os valores das palavras

    Sleep(1000);       // pausa de 1 seg
    srand(time(NULL)); // seta semente para horario do computador do usuario

    if (file) // verifica se file existe caso sim
    {
        for (i = 0; i < numeroPalavras; i++)
        {
            (*MemoriaPCValores)[i] = rand() % 10000000; // memoria principal recebe valores aleatórios
        }
        escreve_arquivo(MemoriaPCValores, numeroPalavras);
    }
    else
    {
        printf("Erro ao abrir o arquivo.\n"); // caso não limpa a memoria
        fclose(file); // caso não fecha o arquivo
        free(*MemoriaPCValores); // e limpa os valores da memoria principal
    }
}

#endif