#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Headers/SAE.h"

void liberarShiftAnd(__int128_t *bitMasks){

    free(bitMasks);
}

__int128_t *gerarBitMasks(char *padrao, int tamPadrao){

    __int128_t* bitMasks = calloc(TAM_ALFABETO, sizeof *bitMasks);
    
    for (int i = 0; i < tamPadrao; i++) {
        
        //'A' = 65, na tabela ascii
        bitMasks[padrao[i] - 65] |= (((__int128_t)1) << (tamPadrao - i - 1));
    }

    return bitMasks;
}

int shiftAndExato(char *texto, int tamanhoTexto, int tamanhoPadrao, __int128_t *bitMasks) {
    
    //R representa a mascara de bits do caracter atual selecionado na bitMasks .
    __int128_t R = 0;
    
    for (int i = 0; i < tamanhoTexto; i++) {

        R = ((R >> 1) | (((__int128_t)1) << (tamanhoPadrao - 1))) & bitMasks[texto[i] - 65];

        if ((R & 1) != 0) {
            
            return i - tamanhoPadrao + 1; 
        }
    }

    return -1;
}
