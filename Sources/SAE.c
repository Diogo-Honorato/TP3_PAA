#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Headers/SAE.h"

__int128_t **iniciarBitMasks(){

    __int128_t **bitMasks = calloc(3, sizeof *bitMasks);

    for(int i = 0; i < 3; i++){

        bitMasks[i] = calloc(TAM_ALFABETO, sizeof **bitMasks);
    }

    return bitMasks;
}

void liberarBitMasks(__int128_t **bitMasks){

    for(int i = 0; i < 3; i++){

        free(bitMasks[i]);
    }

    free(bitMasks);
}

__int128_t **gerarBitMasks(char **padrao, int tamanhoPadrao){

    __int128_t **bitMasks = iniciarBitMasks();

    for (int i = 0; i < tamanhoPadrao; i++) {

        int tipo = 0;
        char *caractere = padrao[i];

        switch (caractere[1]) {
            case '#':
                tipo = 1;
                break;

            case 'b':
                tipo = 2;
                break;

            default:
                if (caractere[1] != '\0') {
                    continue;
                }
        }

        bitMasks[tipo][caractere[0] - 'A'] |= ((__int128_t)1 << i);
    }

    return bitMasks;
}

int shiftAndExato(char **texto, int tamanhoTexto, int tamanhoPadrao, __int128_t **bitMasks) {
    
    __int128_t matching = 0;

    __int128_t alvo = (__int128_t)1 << (tamanhoPadrao - 1); 

    for (int i = 0; i < tamanhoTexto; i++) {
        
        matching = (matching << 1) | (__int128_t)1;

        int tipo = 0;
        
        switch (texto[i][1]) {
            case '#': 
                tipo = 1;
                break;

            case 'b':
                tipo = 2;
                break;

            default:
                if (texto[i][1] != '\0') {
                    printf("\nCaracter inválido\n");
                    return -1;
                }
                break;
        }

        __int128_t mascara = bitMasks[tipo][texto[i][0] - 'A'];

        matching &= mascara;

        if (matching & alvo) {

            return i - tamanhoPadrao + 1;
        }
    }

    return -1;
}
