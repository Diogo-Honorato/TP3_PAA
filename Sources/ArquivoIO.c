#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ArquivoIO.h"

PlagiChecker *lerArquivo(FILE *fileInput)
{

    int tamTexto;
    int tamPadrao;
    char *string = calloc(3, sizeof *string);

    PlagiChecker *plagiChecker = NULL;

    if (fscanf(fileInput, "%d %d ", &tamTexto, &tamPadrao) == 2)
    {

        if (tamTexto && tamPadrao)
        {

            plagiChecker = iniciarPlagiChecker(tamTexto, tamPadrao);

            for (int i = 0; i < tamTexto; i++)
            {

                if (fscanf(fileInput, "%s", string) == EOF)
                {

                    liberarMemoria(plagiChecker);
                    free(string);
                    return NULL;
                }

                plagiChecker->texto[i] = converterString(string);
            }

            for (int j = 0; j < tamPadrao; j++)
            {

                if (fscanf(fileInput, "%s", string) == EOF)
                {

                    liberarMemoria(plagiChecker);
                    free(string);
                    return NULL;
                }

                plagiChecker->padrao[j] = converterString(string);
            }
        }
        else
        {

            free(plagiChecker);
            free(string);
            return NULL;
        }
    }
    else
    {

        free(plagiChecker);
        free(string);
        return NULL;
    }

    free(string);
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
    
    fclose(fileOutput);
}

void saidaArquivoTempos(const char *CAMINHO_ARQUIVO, int algoritmo, int numTeste,double tempoUsuario, double tempoSistema, double tempoRuUsage, double tempoGetTimeofDay)
{

    FILE *fileOutput;

    fileOutput = fopen(CAMINHO_ARQUIVO, "a");

    switch (algoritmo)
    {
    case 1:
    
        fprintf(fileOutput, "\n---Tempo de execucao do algoritmo Força Bruta, teste: %d---\n",numTeste);    
        break;

    case 2:
        
        fprintf(fileOutput, "\n---Tempo de execucao do algoritmo KMP, teste: %d---\n",numTeste);
        break;

    case 3:
        
        fprintf(fileOutput, "\n---Tempo de execucao do algoritmo BMH, teste: %d---\n",numTeste);
        break;

    case 4:
    
        fprintf(fileOutput, "\n---Tempo de execucao do algoritmo Shift-And Exato, teste: %d---\n",numTeste);
        break;

    default:

        break;
    }

    
    fprintf(fileOutput, "\nTempo em microssegundos:\n");
    fprintf(fileOutput, "Tempo Usuario = %.3f microssegundos\n", tempoUsuario);
    fprintf(fileOutput, "Tempo Sistema = %.3f microssegundos\n", tempoSistema);
    fprintf(fileOutput, "Tempo rusage = %.3f microssegundos\n", tempoRuUsage);
    fprintf(fileOutput, "Tempo gettimeofday = %.3f microssegundos\n", tempoGetTimeofDay);

    fprintf(fileOutput, "\nTempo em segundos:\n");
    fprintf(fileOutput, "Tempo Usuario = %.3f segundos\n", tempoUsuario / 1000000);
    fprintf(fileOutput, "Tempo Sistema = %.3f segundos\n", tempoSistema / 1000000);
    fprintf(fileOutput, "Tempo rusage = %.3f segundos\n", tempoRuUsage / 1000000);
    fprintf(fileOutput, "Tempo gettimeofday = %.3f segundos\n\n\n", tempoGetTimeofDay / 1000000); 

    fclose(fileOutput);
}

void saidaDadosGrafico(const char *CAMINHO,double GetTimeOfDay,double Rusage){


    FILE *file;

    file = fopen(CAMINHO,"a");

    fprintf(file, "%.2lf %.2lf\n",GetTimeOfDay,Rusage);

    fclose(file);
}