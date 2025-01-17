#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ArquivoIO.h"

PlagiChecker *lerArquivo(FILE *fileInput)
{

    int tamTexto;
    int tamPadrao;
    PlagiChecker *plagiChecker = NULL;

    if (fscanf(fileInput, "%d %d ", &tamTexto, &tamPadrao) == 2)
    {

        if (tamTexto && tamPadrao)
        {

            plagiChecker = iniciarPlagiChecker(tamTexto, tamPadrao);

            for (int i = 0; i < tamTexto; i++)
            {

                if (fscanf(fileInput, "%s", plagiChecker->texto[i]) == EOF)
                {

                    liberarMemoria(plagiChecker);
                    return NULL;
                }
            }

            for (int j = 0; j < tamPadrao; j++)
            {

                if (fscanf(fileInput, "%s", plagiChecker->padrao[j]) == EOF)
                {

                    liberarMemoria(plagiChecker);
                    return NULL;
                }
            }
        }
        else
        {

            free(plagiChecker);
            return NULL;
        }
    }
    else
    {

        free(plagiChecker);
        return NULL;
    }

    return plagiChecker;
}

void saidaArquivoResultado(const char *CAMINHO_ARQUIVO, int indiceInicio)
{

    FILE *fileOutput;

    fileOutput = fopen(CAMINHO_ARQUIVO, "a");

    if (indiceInicio >= 0)
    {

        fprintf(fileOutput, "S %d\n", indiceInicio);
    }
    else
    {

        fprintf(fileOutput, "N\n");
    }
    printf("\nArquivo de resultados dos testes gerado com sucesso no caminho: %s\n",CAMINHO_ARQUIVO);
    fclose(fileOutput);
}

void saidaArquivoTempos(const char *CAMINHO_ARQUIVO, int algoritmo, double tempoUsuario, double tempoSistema, double tempoRuUsage, double tempoGetTimeofDay)
{

    FILE *fileOutput;

    fileOutput = fopen(CAMINHO_ARQUIVO, "a");

    switch (algoritmo)
    {
    case 1:
    
        fprintf(fileOutput, "\n---Tempo de execucao do algoritmo Força Bruta---\n");    
        break;

    case 2:
        
        fprintf(fileOutput, "\n---Tempo de execucao do algoritmo KMP---\n");
        break;

    case 3:
        
        fprintf(fileOutput, "\n---Tempo de execucao do algoritmo BMH---\n");
        break;

    case 4:
    
        fprintf(fileOutput, "\n---Tempo de execucao do algoritmo Shift-And exato---\n");
        break;

    default:

        break;
    }

    
    fprintf(fileOutput, "\nTempo em microssegunods:\n");
    fprintf(fileOutput, "Tempo Usuario = %.3f microssegundos\n", tempoUsuario);
    fprintf(fileOutput, "Tempo Sistema = %.3f microssegundos\n", tempoSistema);
    fprintf(fileOutput, "Tempo rusage = %.3f microssegundos\n", tempoRuUsage);
    fprintf(fileOutput, "Tempo gettimeofday = %.3f microssegundos\n", tempoGetTimeofDay);

    fprintf(fileOutput, "\nTempo em segundos:\n");
    fprintf(fileOutput, "Tempo Usuario = %.3f segundos\n", tempoUsuario / 1000000);
    fprintf(fileOutput, "Tempo Sistema = %.3f segundos\n", tempoSistema / 1000000);
    fprintf(fileOutput, "Tempo rusage = %.3f segundos\n", tempoRuUsage / 1000000);
    fprintf(fileOutput, "Tempo gettimeofday = %.3f segundos\n\n\n", tempoGetTimeofDay / 1000000);

    printf("\nArquivo de benchmark gerado com sucesso no caminho: %s!\n",CAMINHO_ARQUIVO);;
}