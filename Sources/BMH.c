#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxTamAlfabeto 127

int BMH(char *texto, int tamTexto, char *padrao, int tamPadrao, int *tabela, int *numComp) {
    int i, j, k;

    i = tamPadrao;
    // Pesquisa
    while (i <= tamTexto) {
        k = i;
        j = tamPadrao - 1;
        while (j >= 0 && texto[k - 1] == padrao[j]) {
            k--;
            j--;
            *numComp = *numComp + 1;
        }
        if (j < 0) {
            return k;
        }
        i += tabela[(unsigned char)texto[i - 1]];
        *numComp = *numComp + 1;
    }
    return -1;
}

int *processamento(char *padrao, int tamPadrao){
    int j;
    int *tabela = malloc(MaxTamAlfabeto * sizeof *tabela);

    // Pré-processamento do padrão
    for (j = 0; j < MaxTamAlfabeto; j++) {
        tabela[j] = tamPadrao;
    }
    for (j = 0; j < tamPadrao - 1; j++) {
        tabela[(unsigned char)padrao[j]] = tamPadrao - 1 - j;
    }
    return tabela;
}