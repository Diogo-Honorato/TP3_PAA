// local onde sera feito o calculo do tempo e o teste de cada elemento da entrada.

#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ArquivoIO.h"
#include "../Headers/ForcaBruta.h"
#include "../Headers/KMP.h"
#include "../Headers/SAE.h"
#include "../Headers/Benchmark.h"
#include "../Headers/GerenciarTempo.h"

void benchmark(const int algoritmo, char **texto, char **padrao, int tamTexto, int tamPadrao)
{

    int resultado = -1;

    switch (algoritmo)
    {
    case 1:

        resultado = forcaBruta(texto, padrao, tamTexto, tamPadrao);
        break;

    case 2:

        resultado = kmp(texto, padrao, tamTexto, tamPadrao);
        break;

    case 4:

        resultado = shiftAndExato(texto,padrao,tamTexto,tamPadrao);
        break;
        
    default:
        perror("Nenhum algoritmo encontrado com essa tag!");
        break;
    }

    saidaArquivoResultado("saida.txt", resultado);
}