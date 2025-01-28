#ifndef BMH_H
#define BMH_H

#define MaxTamAlfabeto 127

int BMH(char *texto, int tamTexto, char *padrao, int tamPadrao, int *tabela, int *numComp);
int *processamento(char *padrao, int tamPadrao);

#endif