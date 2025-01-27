#include <stdio.h>
#include <string.h>

#define MaxTamAlfabeto 256

void BMH(char T[], int n, char P[], int m) {
    int i, j, k;
    int d[MaxTamAlfabeto];

    // Pré-processamento do padrão
    for (j = 0; j < MaxTamAlfabeto; j++) {
        d[j] = m;
    }
    for (j = 0; j < m - 1; j++) {
        d[(unsigned char)P[j]] = m - 1 - j;
    }

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
            printf("Casamento na posição: %d\n", k + 1);
        }
        i += d[(unsigned char)T[i - 1]];
    }
}

int main() {
    char T[] = "exemplo de texto para busca"; // Texto principal
    char P[] = "texto"; // Padrão a ser buscado
    int n = strlen(T);
    int m = strlen(P);

    BMH(T, n, P, m);

    return 0;
}
