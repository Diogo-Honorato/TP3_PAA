// local onde sera feito o calculo do tempo e o teste de cada elemento da entrada.

#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ArquivoIO.h"
#include "../Headers/ForcaBruta.h"
#include "../Headers/KMP.h"
#include "../Headers/SAE.h"
#include "../Headers/Benchmark.h"
#include "../Headers/GerenciarTempo.h"

void benchmark(const int algoritmo, int numTeste, char *texto, char *padrao, int tamTexto, int tamPadrao)
{
    struct timeval tempoInicio, tempoFim, tempoDiferenca;

    double tempoUsuarioInicio, tempoUsuarioFim, tempoSistemaInicio, tempoSistemaFim;
    
    double tempoUsuarioCompleto, tempoSistemaCompleto, tempoGetTimeofDay, tempoRuUsage;

    int resultado = -1;

    __int128_t *bitMasks;
    int *tabela;

    if(tamTexto < tamPadrao){
        
        printf("\nTexto menor que o padrao.\n\n");
        return;
    }

    switch (algoritmo)
    {
    case 1:
        // Obtendo o tempo de início do sistema juntamente com o do usuario
        getUsageNow(&tempoUsuarioInicio, &tempoSistemaInicio);
        gettimeofday(&tempoInicio, NULL);

        resultado = forcaBruta(texto, padrao, tamTexto, tamPadrao);

        // Obtém o tempo do fim da execução.
        getUsageNow(&tempoUsuarioFim, &tempoSistemaFim);
        gettimeofday(&tempoFim, NULL);
        
        break;

    case 2:

        tabela = preProcessamento(padrao, tamPadrao);

        getUsageNow(&tempoUsuarioInicio, &tempoSistemaInicio);
        gettimeofday(&tempoInicio, NULL);

        resultado = kmp(texto, padrao, tamTexto, tamPadrao, tabela);
        
        getUsageNow(&tempoUsuarioFim, &tempoSistemaFim);
        gettimeofday(&tempoFim, NULL);

        free(tabela);

        break;

    case 4:

        bitMasks = gerarBitMasks(padrao,tamPadrao);

        getUsageNow(&tempoUsuarioInicio, &tempoSistemaInicio);
        gettimeofday(&tempoInicio, NULL);

        resultado = shiftAndExato(texto,tamTexto,tamPadrao,bitMasks);
        
        getUsageNow(&tempoUsuarioFim, &tempoSistemaFim);
        gettimeofday(&tempoFim, NULL);

        liberarShiftAnd(bitMasks);
        break;
        
    default:
        perror("Nenhum algoritmo encontrado com essa tag!");
        break;
    }

    timeval_subtract(&tempoDiferenca, &tempoFim, &tempoInicio);

    tempoGetTimeofDay = joinTimes(tempoDiferenca.tv_sec, tempoDiferenca.tv_usec);
    tempoUsuarioCompleto = tempoUsuarioFim - tempoUsuarioInicio;
    tempoSistemaCompleto = tempoSistemaFim - tempoSistemaInicio;
    tempoRuUsage = tempoUsuarioCompleto + tempoSistemaCompleto;

    saidaArquivoTempos("Resultados/benchmark.txt",algoritmo,numTeste,tempoUsuarioCompleto,tempoSistemaCompleto,tempoRuUsage,tempoGetTimeofDay);

    saidaArquivoResultado("Resultados/saida.txt", resultado);

    saidaDadosGrafico("Resultados/Dados.txt",tempoGetTimeofDay,resultado);
}