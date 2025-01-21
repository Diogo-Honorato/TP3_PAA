#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/ForcaBruta.h"

int forcaBruta(char *texto, char *padrao, int tamanhoTexto, int tamanhoPadrao)
{

    int j, k;

    if (tamanhoTexto < tamanhoPadrao)
    {
        return -1;
    }

    for (int i = 0; i <= (tamanhoTexto - tamanhoPadrao); i++)
    {

        k = i;
        j = 0;

        while (j < tamanhoPadrao && texto[k] == padrao[j])
        {
            j = j + 1;
            k = k + 1;
        }

        if (j == tamanhoPadrao)
        {
            return i;
        }
    }

    return -1;
}