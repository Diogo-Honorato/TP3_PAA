#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Headers/SAE.h"

__int128_t *gerarBitMasks(char *padrao, int tamPadrao){

    __int128_t* bitMasks = calloc(TAM_ALFABETO, sizeof *bitMasks);
    
    for (int i = 0; i < tamPadrao; i++) {
        
        bitMasks[(unsigned char)padrao[i]] |= (((__int128_t)1) << (tamPadrao - i - 1));
    }

    return bitMasks;
}

int shiftAndExato(char *texto, int tamanhoTexto, int tamanhoPadrao, __int128_t *bitMasks, int *numComp) {
    
    //R representa a mascara de bits do caracter atual selecionado na bitMasks.
    __int128_t R = 0;

    for (int i = 0; i < tamanhoTexto; i++) {

        R = ((R >> 1) | (((__int128_t)1) << (tamanhoPadrao - 1))) & bitMasks[(unsigned char)texto[i]];

        if ((R & 1) != 0) {
            *numComp = *numComp + 1;

            return (i - tamanhoPadrao + 1); 
        }
        *numComp = *numComp + 1;
    }

    return -1;
}