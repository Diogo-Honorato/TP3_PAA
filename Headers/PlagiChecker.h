#ifndef _PLAGICHECKER_H_
#define _PLAGICHECKER_H_

typedef struct PlagiChecker{

int tamanhoTexto;
int tamanhoPadrao;
char **texto;
char **padrao;

}PlagiChecker;

PlagiChecker *iniciarPlagiChecker(int tamanhoTexto, int tamanhoPadrao);

void liberarMemoria(PlagiChecker *plagiChecker);

void imprimirPlagiChecker(PlagiChecker *plagiChecker);

#endif