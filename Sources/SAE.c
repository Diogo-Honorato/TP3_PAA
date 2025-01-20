#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Headers/SAE.h"

#define TAM_ALFABETO 98

bool primo(int num){

    if (num <= 1){

        return false;
    }
    else if (num == 2) {
        
        return true;
    }
    else if (num % 2 == 0) {
    
        return false;
    }

    // Verifica até a raiz quadrada, pois divisores maiores já seriam encontrados.
    int fim = sqrt(num);

    for (int i = 3; i <= fim; i += 2) {

        if(num % i == 0) {
            
            return false;
        }
    }

    return true;
}

int hashSize(int tamDados){
    
    //fator de carga para 76%.
    int tamanhoHash = tamDados / 0.76;
    
    if (tamanhoHash * 0.76 < tamDados) {
        tamanhoHash++;
    }
    
    while (!primo(tamanhoHash)) {
        tamanhoHash++;
    }

    return tamanhoHash;   
}

HashMap *iniciarHashMap(int totalDados){

    HashMap *map = calloc(1, sizeof *map);

    int tamanhoHash = hashSize(totalDados);

    map->array = calloc(tamanhoHash, sizeof *map->array);
    map->hashSize = tamanhoHash;

    for(int i = 0; i < tamanhoHash; i++){

        map->array[i].chave = NULL;
        map->array[i].valor = (__int128_t)0;
    }
    
    return map;
}

char *strdup(const char *s) {

    char *dup = malloc(strlen(s) + 1);

    if (dup != NULL) {
        strcpy(dup, s);
    }
    
    return dup;
}

int hashing(const char *chave, int hashSize) {

    unsigned long hash = 5381;
    while (*chave) {
        hash = ((hash << 5) + hash) + *chave;
        chave++;
    }
    return hash % hashSize;
}

int inserirDados(HashMap *map, char *chave, __int128_t valor){

    int indice = hashing(chave,map->hashSize);

    while (map->array[indice].chave != NULL)
    {
        if (strcmp(map->array[indice].chave,chave) == 0)
        {
            map->array[indice].valor = valor;
            return indice;
        }
        
        indice = (indice + 1) % map->hashSize;
    }

    map->array[indice].chave = strdup(chave);
    map->array[indice].valor = valor;

    return indice;
}

__int128_t buscarMascara(HashMap *map, char *chave) {

    int indice = hashing(chave, map->hashSize);
    while (map->array[indice].chave != NULL) {
        if (strcmp(map->array[indice].chave, chave) == 0) {
            return map->array[indice].valor;
        }
        indice = (indice + 1) % map->hashSize;
    }
    return 0;
}

void liberarHashMap(HashMap *map){

    for (int i = 0; i < map->hashSize; i++) {

        if (map->array[i].chave != NULL) {
            free(map->array[i].chave);
        }
    }
    free(map->array);
    free(map);
}

HashMap* criarBitMasks(char **padrao, int tamanhoPadrao) {
    
    HashMap *bitMasks = iniciarHashMap(TAM_ALFABETO);

    for (int i = 0; i < tamanhoPadrao; i++) {

        __int128_t mascara = buscarMascara(bitMasks, padrao[i]);

        if (mascara == 0) { 

            mascara = ((__int128_t)1 << i);

        } else {

            mascara |= ((__int128_t)1 << i);
        }

        inserirDados(bitMasks, padrao[i], mascara);
    }

    return bitMasks;
}

int shiftAndExato(char **texto, int tamanhoTexto, int tamanhoPadrao, HashMap *bitMasks) {
    
    __int128_t matching = 0;

    __int128_t alvo = (__int128_t)1 << (tamanhoPadrao - 1);
    

    for (int i = 0; i < tamanhoTexto; i++) {

        matching = (matching >> (__int128_t)1) | (__int128_t)1;

        __int128_t mascara = buscarMascara(bitMasks, texto[i]);

        matching &= mascara;

        if (matching & alvo) {

            return i - tamanhoPadrao + 1;
        }
    }

    return -1;
}
