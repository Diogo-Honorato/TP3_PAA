#ifndef _KMP_H_
#define _KMP_H_

int kmp(char *texto, char *padrao, int tamanhoTexto, int tamanhoPadrao, int *tabela);

int *preProcessamento(char *padrao, int tamanhoPadrao);


#endif