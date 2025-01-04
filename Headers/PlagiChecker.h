#ifndef _PLAGICHECKER_H
#define _PLAGICHECKER_H

typedef struct PlagiChecker{

int tamanhoString;
int tamanhoSubString;
char **string;
char **subString;

}PlagiChecker;

PlagiChecker *iniciarPlagiChecker(int tamanhoString, int tamanhoSubString);

#endif