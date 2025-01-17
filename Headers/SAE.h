#ifndef _SAE_H_
#define _SAE_H_
#include <stdbool.h>

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

int hashing(char *chave, int hashSize);

int inserirDados(HashMap *map, char *chave, __int128_t valor);

int buscarChave(HashMap *map, char *chave);

void liberarHashMap(HashMap *map);

int shiftAndExato(char **texto, char **padrao, int tamanhoTexto, int tamanhoPadrao);

#endif