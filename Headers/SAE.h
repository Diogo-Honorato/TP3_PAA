#ifndef _SAE_H_
#define _SAE_H_
#include <stdbool.h>
#define TAM_ALFABETO 21

char *converterTexto(char **texto, int tamTexto);

char *converterPadrao(char **padrao, int tamPadrao);

__int128_t *gerarBitMasks(char *padrao, int tamPadrao);

void liberarShiftAnd(char *texto, char *padrao, __int128_t *bitMasks);

int shiftAndExato(char *texto, int tamanhoTexto, int tamanhoPadrao, __int128_t *bitMasks);

#endif
