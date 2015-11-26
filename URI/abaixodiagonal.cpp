#include <stdio.h>

using namespace std;

int main() {
    char operacao[5];
    double M[12][12], soma = 0, div = 66;

    scanf("%s", operacao);

    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++)
            scanf("%lf", &M[i][j]);

    int res = 0;
    for (int i = 1; i < 12; i++) {
        for (int j = 11-res; j < 12; j++)
            soma += M[i][j];
        res++;
    }

    if (operacao[0] == 'M') soma /= div;

    printf("%.1lf\n", soma);
    return 0;
}
