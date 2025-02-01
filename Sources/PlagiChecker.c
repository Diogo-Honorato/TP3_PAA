#include <stdio.h>
#include <stdlib.h>
#include "../Headers/PlagiChecker.h"

PlagiChecker *iniciarPlagiChecker(int tamanhoTexto, int tamanhoPadrao)
{

    PlagiChecker *plagiChecker = calloc(1, sizeof *plagiChecker);

    plagiChecker->texto = calloc(tamanhoTexto, sizeof *plagiChecker->texto);

    plagiChecker->padrao = calloc(tamanhoPadrao, sizeof *plagiChecker->padrao);

    plagiChecker->tamanhoTexto = tamanhoTexto;
    plagiChecker->tamanhoPadrao = tamanhoPadrao;

    return plagiChecker;
}

void liberarMemoria(PlagiChecker *plagiChecker)
{
    free(plagiChecker->texto);
    free(plagiChecker->padrao);
    free(plagiChecker);
}

char converterString(char *string){

    /*
        converte uma nota com alterações cromáticas '#' ou 'b' para o seu 
        equivalente no alfabeto exemplo: A# = 'H' ,  B# = I , etc...
    */

    switch (string[1])
    {
    case '#':
        return (string[0] + 7);
        break;

    case 'b':
        return (string[0] + 14);
        break;

    default:
        if (string[1] != '\0')
        {
            printf("\nCaracter inválido\n");
            return '\0';
        }
        else
        {

            return string[0];
        }
        break;
    }
}

void imprimirPlagiChecker(PlagiChecker *plagiChecker)
{
    printf("%d %d\n", plagiChecker->tamanhoTexto, plagiChecker->tamanhoPadrao);

    for (int i = 0; i < plagiChecker->tamanhoTexto; i++)
    {

        printf("%c ", plagiChecker->texto[i]);
    }
    printf("\n");
    for (int i = 0; i < plagiChecker->tamanhoPadrao; i++)
    {

        printf("%c ", plagiChecker->padrao[i]);
    }
    printf("\n\n");
}