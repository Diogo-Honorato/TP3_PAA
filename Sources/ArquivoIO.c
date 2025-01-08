#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ArquivoIO.h"


PlagiChecker *lerArquivo(FILE *fileInput)
{

    int tamString;
    int tamSubString;
    PlagiChecker *plagiChecker = NULL;

    if (fscanf(fileInput, "%d %d ", &tamString, &tamSubString) == 2)
    {

        if (tamString && tamSubString)
        {

            plagiChecker = iniciarPlagiChecker(tamString,tamSubString);

            for(int i = 0; i < tamString; i++){

                if(fscanf(fileInput,"%s",plagiChecker->string[i]) == EOF){

                    liberarMemoria(plagiChecker);
                    return NULL;
                }
            }
            
            for(int j = 0; j < tamSubString; j++){

                if(fscanf(fileInput,"%s",plagiChecker->subString[j]) == EOF){
                
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

    if(indiceInicio >= 0){

        fprintf(fileOutput, "S %d\n",indiceInicio);

    }else{

        fprintf(fileOutput, "N\n");
    }
    
    fclose(fileOutput);
}

void saidaArquivoTempos(const char *CAMINHO_ARQUIVO, int numeroTeste, double tempoUsuario, double tempoSistema, double tempoRuUsage, double tempoGetTimeofDay)
{

    FILE *fileOutput;

    fileOutput = fopen(CAMINHO_ARQUIVO, "w");


    fprintf(fileOutput,"\n---Tempo de execucao do teste: %d---\n",numeroTeste);
    fprintf(fileOutput,"\nTempo em microssegunods:\n");
    fprintf(fileOutput,"Tempo Usuario = %.3f microssegundos\n", tempoUsuario);
    fprintf(fileOutput,"Tempo Sistema = %.3f microssegundos\n", tempoSistema);
    fprintf(fileOutput,"Tempo rusage = %.3f microssegundos\n", tempoRuUsage);
    fprintf(fileOutput,"Tempo gettimeofday = %.3f microssegundos\n", tempoGetTimeofDay);

    fprintf(fileOutput,"\nTempo em segundos:\n");
    fprintf(fileOutput,"Tempo Usuario = %.3f segundos\n", tempoUsuario / 1000000);
    fprintf(fileOutput,"Tempo Sistema = %.3f segundos\n", tempoSistema / 1000000);
    fprintf(fileOutput,"Tempo rusage = %.3f segundos\n", tempoRuUsage / 1000000);
    fprintf(fileOutput,"Tempo gettimeofday = %.3f segundos\n\n\n", tempoGetTimeofDay / 1000000);
}