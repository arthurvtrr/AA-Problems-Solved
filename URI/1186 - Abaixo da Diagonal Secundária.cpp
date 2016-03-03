#include <stdio.h>

using namespace std;

int main() {
    char operacao[5];
    double M[15][15], soma = 0, div = 66;

    scanf("%s", operacao);

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++) {
            scanf("%lf", &M[i][j]);
            if (i+j > 11) soma += M[i][j];
        }

    if (operacao[0] == 'M') soma /= div;

    printf("%.1lf\n", soma);
    return 0;
}