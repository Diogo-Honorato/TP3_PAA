#include <stdio.h>
#include <string.h>

#define MaxTamAlfabeto 256

void BMH(char T[], int n, char P[], int m, int *d) {
    int i, j, k;

    i = m;
    // Pesquisa
    while (i <= n) {
        k = i;
        j = m - 1;
        while (T[k - 1] == P[j] && j >= 0) {
            k--;
            j--;
        }
        if (j < 0) {
            printf("Casamento na posição: %d\n", k);
        }
        i += d[(unsigned char)T[i - 1]];
    }
}

int *processamento(char *padrao, int tamPadrao){
    int i, j, k;
    int d[MaxTamAlfabeto];

    // Pré-processamento do padrão
    for (j = 0; j < MaxTamAlfabeto; j++) {
        d[j] = tamPadrao;
    }
    for (j = 0; j < tamPadrao - 1; j++) {
        d[padrao[j]] = tamPadrao - 1 - j;
    }

}

// int main() {
//     char T[] = "Diogo é muito gay"; // Texto principal
//     char P[] = "Diogo"; // Padrão a ser buscado
//     int n = strlen(T);
//     int m = strlen(P);

//     BMH(T, n, P, m);

//     return 0;
// }
