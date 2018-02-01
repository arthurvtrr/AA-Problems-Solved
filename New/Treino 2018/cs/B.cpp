#include <bits/stdc++.h>

using namespace std;

int quant[6][100100];

int main() {
    for (int i = 2; i < 100100; i++) {
        quant[2][i] = quant[2][i-1];
        quant[5][i] = quant[5][i-1];

        int aux = i;
        while (aux % 2 == 0) {
            quant[2][i]++;
            aux /= 2;
        }
        while (aux % 5 == 0) {
            quant[5][i]++;
            aux /= 5;
        }
    }

    int ini = 0, fim = 1000000, x;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        printf("Q %d\n", meio);
        fflush(stdout);
        scanf("%d", &x);
        if (x == 1) ini = meio+1;
        else fim = meio-1;
    }
    for (int i = 5; i <= 100000; i++) {
        if (min(quant[2][i], quant[5][i]) == fim) {
            printf("A %d\n", i);
            fflush(stdout);
            break;
        }
    }

    return 0;
}

