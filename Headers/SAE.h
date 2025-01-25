#ifndef _SAE_H_
#define _SAE_H_
#include <stdbool.h>
#define TAM_ALFABETO 21

__int128_t *gerarBitMasks(char *padrao, int tamPadrao);

void liberarShiftAnd(__int128_t *bitMasks);

int shiftAndExato(char *texto, int tamanhoTexto, int tamanhoPadrao, __int128_t *bitMasks, int *numComp);

#endif
