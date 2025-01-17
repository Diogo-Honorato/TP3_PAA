#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/ArquivoIO.h"
#include "../Headers/Benchmark.h"

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("\n\033[0;31mERRO: Uso incorreto dos argumentos.\033[0m\n");
        printf("\033[0;31mUso correto: %s caminho_entrada.txt algoritmo\033[0m\n\n", argv[0]);
        return 1;
    }

    const char *CAMINHO_ARQUIVO_INPUT = argv[1];
    const char *CAMINHO_ARQUIVO_SAIDA = "Resultados/saida.txt";
    const char *CAMINHO_ARQUIVO_BENCHMARK = "Resultados/benchmark.txt";
    const int algoritmo = atoi(argv[2]);

    PlagiChecker *plagiChecker = NULL;
    int numTeste = 1;

    FILE *fileInput;
    FILE *fileSaida;
    FILE *fileBenchmark;

    fileSaida = fopen(CAMINHO_ARQUIVO_SAIDA,"w");
    if (!fileSaida) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    fileBenchmark = fopen(CAMINHO_ARQUIVO_BENCHMARK,"w");
    if (!fileBenchmark) {
        printf("Erro ao abrir o arquivo de benchmarks.\n");
        return 1;
    }
    fclose(fileSaida);
    fclose(fileBenchmark);


    fileInput = fopen(CAMINHO_ARQUIVO_INPUT, "r");
    if (!fileInput) {
        printf("Erro ao abrir o arquivo de testes.\n");
        return 1;
    }


    while (!feof(fileInput))
    {
        plagiChecker = lerArquivo(fileInput);

        if (plagiChecker == NULL)
        {

            continue;
        }

        benchmark(algoritmo, numTeste, plagiChecker->texto, plagiChecker->padrao, plagiChecker->tamanhoTexto, plagiChecker->tamanhoPadrao);

        liberarMemoria(plagiChecker);
        numTeste++;
    }

    printf("\nArquivo de resultados dos testes gerado com sucesso no caminho: %s\n",CAMINHO_ARQUIVO_SAIDA);
    printf("\nArquivo de benchmark gerado com sucesso no caminho: %s\n\n",CAMINHO_ARQUIVO_BENCHMARK);
    fclose(fileInput);

    return 0;
}