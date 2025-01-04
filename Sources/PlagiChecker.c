#include <stdio.h>
#include <stdlib.h>
#include "../Headers/PlagiChecker.h"

PlagiChecker *iniciarPlagiChecker(int tamanhoString, int tamanhoSubString)
{

    PlagiChecker *plagiChecker = (PlagiChecker *)malloc(sizeof(PlagiChecker));

    plagiChecker->string = (char **)malloc(tamanhoString * sizeof(char *));

    for (int i = 0; i < tamanhoString; i++)
    {

        plagiChecker->string[i] = (char *)malloc(3 * sizeof(char));
    }

    plagiChecker->subString = (char **)malloc(tamanhoSubString * sizeof(char *));
    for (int i = 0; i < tamanhoSubString; i++)
    {

        plagiChecker->subString[i] = (char *)malloc(3 * sizeof(char));
    }

    plagiChecker->tamanhoString = tamanhoString;
    plagiChecker->tamanhoSubString = tamanhoSubString;

    return plagiChecker;
}