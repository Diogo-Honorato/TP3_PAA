#ifndef _ARQUIVOIO_H_
#define _ARQUIVOIO_H_
#include "PlagiChecker.h"
#include <stdio.h>

PlagiChecker *lerArquivo(FILE *fileInput);

void saidaArquivoResultado(const char *CAMINHO_ARQUIVO, int indiceInicio);

void saidaArquivoTempos(const char *CAMINHO_ARQUIVO, int algoritmo, int numTeste,double tempoUsuario, double tempoSistema, double tempoRuUsage, double tempoGetTimeofDay);

void saidaDadosGrafico(const char *CAMINHO,double GetTimeOfDay,double Rusage);

#endif