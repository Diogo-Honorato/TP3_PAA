#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../Headers/SAE.h"

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

int hashing(char *chave, int hashSize){

    int indice = 0;

    while(*chave){

        indice = indice + *chave;

        chave++;
    }

    return indice % hashSize;
}

int inserirDados(HashMap *map, char *chave, __int128_t valor){

    int indice = hashing(chave,map->hashSize);

    while (map->array[indice].chave != NULL)
    {
        if (strcmp(map->array[indice].chave,chave) == 0)
        {
            map->array[indice].valor = valor;
            return 0;
        }
        
        indice = (indice + 1) % map->hashSize;
    }

    map->array[indice].chave = chave;
    map->array[indice].valor = valor;

    return 0;
}

int buscarChave(HashMap *map, char *chave){

    int indice = hashing(chave,map->hashSize);

    while (strcmp(map->array[indice].chave,chave) != 0)
    {

        indice = (indice + 1) % map->hashSize;
    }

    return indice;
}

void liberarHashMap(HashMap *map){

    free(map->array);
    free(map);
}