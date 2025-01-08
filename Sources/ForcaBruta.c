#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/ForcaBruta.h"

int forcaBruta(char **string, char **subString, int tamanhoString, int tamanhoSubString){

    int j,k;

    for(int i = 0; i <= (tamanhoString - tamanhoSubString); i++){

        k = i;
        j = 0;

        while (j < tamanhoSubString && strcmp(string[k],subString[j]) == 0)
        {
            printf("string:%s == %s\n",string[k],subString[j]);
            printf("j:%d\n k:%d\n",j,k);
            j = j + 1;
            k = k + 1;
        }

        printf("j saida:%d\n",j);
        if( j == tamanhoSubString){

            printf("indiciInicio:%d\n",j);
            return i;
        }
    }

    return -1;
}