#ifndef _SAE_H_
#define _SAE_H_

typedef struct Item{

    char *chave;
    __int128_t valor;

}Item;

typedef struct HashMap{

    Item *array;
    
}HashMap;


#endif