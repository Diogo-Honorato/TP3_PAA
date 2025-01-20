#ifndef _SAE_H_
#define _SAE_H_
#include <stdbool.h>
#define TAM_ALFABETO 98

typedef struct Item{

    char *chave;
    __int128_t valor;

}Item;

typedef struct HashMap{

    Item *array;
    int hashSize;

}HashMap;

bool primo(int num);

int hashSize(int tamDados);

HashMap *iniciarHashMap(int totalDados);

char *strdup(const char *s);

int hashing(const char *chave, int hashSize);

int inserirDados(HashMap *map, char *chave, __int128_t valor);

__int128_t buscarMascara(HashMap *map, char *chave);

void liberarHashMap(HashMap *map);

HashMap *criarBitMasks(char **padrao, int tamanhoPadrao);

int shiftAndExato(char **texto, int tamanhoTexto, int tamanhoPadrao, HashMap *bitMasks);

#endif
