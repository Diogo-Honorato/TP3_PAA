#ifndef _SAE_H_
#define _SAE_H_
#include <stdbool.h>
#define TAM_ALFABETO 7

__int128_t **iniciarBitMasks();

void liberarBitMasks(__int128_t **bitMasks);

__int128_t **gerarBitMasks(char **padrao, int tamanhoPadrao);

int shiftAndExato(char **texto, int tamanhoTexto, int tamanhoPadrao, __int128_t **bitMasks);

#endif
