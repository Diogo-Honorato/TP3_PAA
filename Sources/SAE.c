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
            return indice;
        }
        
        indice = (indice + 1) % map->hashSize;
    }

    map->array[indice].chave = chave;
    map->array[indice].valor = valor;

    return indice;
}

int buscarChave(HashMap *map, char *chave){

    int indice = hashing(chave,map->hashSize);
    int count = 0;

    while (map->array[indice].chave != NULL && strcmp(map->array[indice].chave,chave) != 0)
    {
        indice = (indice + 1) % map->hashSize;

        if((count + 1) == map->hashSize){

            return -1;
        }

        count++;
    }

    return indice;
}

void liberarHashMap(HashMap *map){

    free(map->array);
    free(map);
}

int shiftAndExato(char **texto, char **padrao, int tamanhoTexto, int tamanhoPadrao) {

    if(tamanhoTexto < tamanhoPadrao){

        return -1;
    }
    
    int indice;
    __int128_t matching = 0;
    HashMap *bitMask = iniciarHashMap(tamanhoPadrao);
    
    //gerando a mascara de bits.
    for(int i = 0; i < tamanhoPadrao; i++){

        inserirDados(bitMask,padrao[i],(__int128_t)0);
    }

    
    for (int i = 0; i < tamanhoPadrao; i++) {

        bitMask->array[buscarChave(bitMask,padrao[i])].valor |= (__int128_t)1 << i;
    }



    //Shift-And exato
    for (int i = 0; i < tamanhoTexto; i++) {

        indice = buscarChave(bitMask,texto[i]);

        if(indice == -1){

            matching = ((matching << 1) | 1) & (__int128_t)0;
        }
        else{

            matching = ((matching << 1) | 1) & bitMask->array[indice].valor;
        }

        if (matching & (__int128_t)1 << (tamanhoPadrao - 1)) {

            return i - tamanhoPadrao + 1;
        }
    }

    liberarHashMap(bitMask);
    
    return -1;
}