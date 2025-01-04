#include <stdio.h>
#include <stdlib.h>
#include "../Headers/PlagiChecker.h"

PlagiChecker *iniciarPlagiChecker(int tamanhoString, int tamanhoSubString)
{

    PlagiChecker *plagiChecker = malloc(sizeof *plagiChecker);


    plagiChecker->string = malloc(tamanhoString * sizeof *plagiChecker->string);
    for (int i = 0; i < tamanhoString; i++)
    {
        plagiChecker->string[i] = malloc(3 * sizeof **plagiChecker->string);
    }
    

    plagiChecker->subString = malloc(tamanhoSubString * sizeof *plagiChecker->subString);
    for (int i = 0; i < tamanhoSubString; i++)
    {

        plagiChecker->subString[i] = malloc(3 * sizeof **plagiChecker->subString);
    }

    plagiChecker->tamanhoString = tamanhoString;
    plagiChecker->tamanhoSubString = tamanhoSubString;

    return plagiChecker;
}