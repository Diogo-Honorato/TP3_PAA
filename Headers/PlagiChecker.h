#ifndef _PLAGICHECKER_H_
#define _PLAGICHECKER_H_

typedef struct PlagiChecker{

int tamanhoString;
int tamanhoSubString;
char **string;
char **subString;

}PlagiChecker;

PlagiChecker *iniciarPlagiChecker(int tamanhoString, int tamanhoSubString);

void liberarMemoria(PlagiChecker *plagiChecker);

void imprimirPlagiChecker(PlagiChecker *plagiChecker);

#endif