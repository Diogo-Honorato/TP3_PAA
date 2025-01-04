#include <stdio.h>
#include <stdlib.h>
#include "../Headers/LiberarMemoria.h"

void liberarMemoria(PlagiChecker *plagiChecker){

    for(int i = 0; i < plagiChecker->tamanhoString; i++){

        free(plagiChecker->string[i]);
    }

    for(int i = 0; i < plagiChecker->tamanhoSubString; i++){

        free(plagiChecker->subString[i]);
    }

    free(plagiChecker->string);
    free(plagiChecker->subString);
    free(plagiChecker);
}