#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/KMP.h"

int kmp(char *texto, char *padrao, int tamanhoTexto, int tamanhoPadrao, int *tabela)
{
    
    int i = 0;
    int j = 0;
    int comp = 0;
    while (i < tamanhoTexto && j < tamanhoPadrao)
    {
        if (texto[i] == padrao[j])
        {
            i++;
            j++;
            comp++;
        }
        else if (j > 0)
        {
            j = tabela[j - 1];
            comp++;
        }
        else
        {

            i++;
            comp++;
        }
    }

    if (j == tamanhoPadrao)
    {
        return comp;
    }

    return -1;
}

int *preProcessamento(char *padrao, int tamanhoPadrao)
{

    int *tabela = calloc(tamanhoPadrao, sizeof *tabela);

    int indice = 0;

    int j = 1;

    while (j < tamanhoPadrao)
    {

        if (padrao[indice] == padrao[j])
        {

            indice++;
            tabela[j] = indice;
            j++;
        }
        else if (indice > 0)
        {

            indice = tabela[indice - 1];
        }
        else
        {

            j++;
        }
    }

    return tabela;
}