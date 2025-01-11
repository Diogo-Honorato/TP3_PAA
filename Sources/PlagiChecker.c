#include <stdio.h>
#include <stdlib.h>
#include "../Headers/PlagiChecker.h"

PlagiChecker *iniciarPlagiChecker(int tamanhoTexto, int tamanhoPadrao)
{

    PlagiChecker *plagiChecker = calloc(1, sizeof *plagiChecker);

    plagiChecker->texto = calloc(tamanhoTexto, sizeof *plagiChecker->texto);
    for (int i = 0; i < tamanhoTexto; i++)
    {
        plagiChecker->texto[i] = calloc(3, sizeof **plagiChecker->texto);
    }

    plagiChecker->padrao = calloc(tamanhoPadrao, sizeof *plagiChecker->padrao);
    for (int i = 0; i < tamanhoPadrao; i++)
    {

        plagiChecker->padrao[i] = calloc(3, sizeof **plagiChecker->padrao);
    }

    plagiChecker->tamanhoTexto = tamanhoTexto;
    plagiChecker->tamanhoPadrao = tamanhoPadrao;

    return plagiChecker;
}

void liberarMemoria(PlagiChecker *plagiChecker)
{

    for (int i = 0; i < plagiChecker->tamanhoTexto; i++)
    {

        free(plagiChecker->texto[i]);
    }

    for (int i = 0; i < plagiChecker->tamanhoPadrao; i++)
    {

        free(plagiChecker->padrao[i]);
    }

    free(plagiChecker->texto);
    free(plagiChecker->padrao);
    free(plagiChecker);
}

void imprimirPlagiChecker(PlagiChecker *plagiChecker)
{
    printf("%d %d\n", plagiChecker->tamanhoTexto, plagiChecker->tamanhoPadrao);

    for (int i = 0; i < plagiChecker->tamanhoTexto; i++)
    {

        printf("%s ", plagiChecker->texto[i]);
    }
    printf("\n");
    for (int i = 0; i < plagiChecker->tamanhoPadrao; i++)
    {

        printf("%s ", plagiChecker->padrao[i]);
    }
    printf("\n\n");
}