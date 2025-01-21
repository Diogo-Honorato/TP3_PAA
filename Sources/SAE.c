#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Headers/SAE.h"

char *converterTexto(char **texto, int tamTexto){

    char *textoConvertido = calloc(tamTexto, sizeof *textoConvertido);

    //converter Texto
    for(int i = 0 ; i < tamTexto; i++){

        switch (texto[i][1]) {
            case '#':
                textoConvertido[i] = (texto[i][0] + 7);
                break;

            case 'b':
                textoConvertido[i] = (texto[i][0] + 14);
                break;

            default:
                if (texto[i][1] != '\0') {
                    printf("\nCaracter inválido\n");
                    return NULL;

                }else{

                    textoConvertido[i] = texto[i][0];
                }
                break;
        }

    }

    return textoConvertido;
}

char *converterPadrao(char **padrao, int tamPadrao){

    char *padraoConvertido = calloc(tamPadrao, sizeof *padraoConvertido);

    //converter o padrao
    for(int i = 0 ; i < tamPadrao; i++){

        switch (padrao[i][1]) {
            case '#':
                padraoConvertido[i] = (padrao[i][0] + 7);
                break;

            case 'b':
                padraoConvertido[i] = (padrao[i][0] + 14);
                break;

            default:
                if (padrao[i][1] != '\0') {
                    printf("\nCaracter inválido\n");
                    return NULL;
                    
                }else{

                    padraoConvertido[i] = padrao[i][0];
                }
                break;
        }

    }

    return padraoConvertido;
}

void liberarShiftAnd(char *texto, char *padrao, __int128_t *bitMasks){

    free(bitMasks);
    free(padrao);
    free(texto);
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
    
    __int128_t alvo = (__int128_t)1 << (tamanhoPadrao - 1);

    for (int i = 0; i < tamanhoTexto; i++) {
        
        matching = (matching << 1) | (__int128_t)1;

        __int128_t mascara = bitMasks[texto[i] - 'A'];

        matching &= mascara; 

        if (matching & alvo) {

            return i - tamanhoPadrao + 1;
        }
    }

    return -1;
}
