#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("\n\033[0;31mERRO: Uso incorreto dos argumentos.\033[0m\n");
        printf("\033[0;31mUso correto: %s caminho_entrada.txt algoritmo\033[0m\n\n", argv[0]);
        return 0;
    }


    printf("hello world!");

    return 1;
}