#include <stdio.h>
#include <stdlib.h>
#include "../Headers/PlagiChecker.h"

PlagiChecker *iniciarPlagiChecker(int tamanhoString, int tamanhoSubString)
{

    PlagiChecker *plagiChecker = calloc(1,sizeof *plagiChecker);

    plagiChecker->string = calloc(tamanhoString, sizeof *plagiChecker->string);
    for (int i = 0; i < tamanhoString; i++)
    {
        plagiChecker->string[i] = calloc(3, sizeof **plagiChecker->string);
    }


    plagiChecker->subString = calloc(tamanhoSubString, sizeof *plagiChecker->subString);
    for (int i = 0; i < tamanhoSubString; i++)
    {

        plagiChecker->subString[i] = calloc(3, sizeof **plagiChecker->subString);
    }

    plagiChecker->tamanhoString = tamanhoString;
    plagiChecker->tamanhoSubString = tamanhoSubString;

    return plagiChecker;
}