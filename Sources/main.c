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
    const int algoritmo = atoi(argv[2]);

    PlagiChecker *plagiChecker = NULL;

    FILE *fileInput;

    fileInput = fopen(CAMINHO_ARQUIVO_INPUT, "r");

    while (!feof(fileInput))
    {
        plagiChecker = lerArquivo(fileInput);

        if (plagiChecker == NULL)
        {

            continue;
        }

        benchmark(algoritmo, plagiChecker->texto, plagiChecker->padrao, plagiChecker->tamanhoTexto, plagiChecker->tamanhoPadrao);

        liberarMemoria(plagiChecker);
    }

    fclose(fileInput);

    return 0;
}