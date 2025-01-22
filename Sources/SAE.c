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
    
        __int128_t mascara = (__int128_t)1 << i;

        bitMasks[padrao[i] - 'A'] |= mascara;
    }

    return bitMasks;
}

int shiftAndExato(char *texto, int tamanhoTexto, int tamanhoPadrao, __int128_t *bitMasks) {
    
    __int128_t matching = 0;
    
    for (int i = 0; i < tamanhoTexto; i++) {
        
        matching = (matching << 1) | (__int128_t)1;

        matching &= bitMasks[texto[i] - 'A'];

         if (matching & ((__int128_t)1 << (tamanhoPadrao - 1))) {
            
            return i - tamanhoPadrao + 1; 
        }
    }
    
    return -1;
}
