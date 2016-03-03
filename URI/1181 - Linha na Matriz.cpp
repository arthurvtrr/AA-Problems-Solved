#include <stdio.h>
#include <string.h>

int main() {
    int i, j, y;
    float soma = 0, x[12][12];
    char o[3];

    scanf("%d", &y);
    scanf("%s", o);

    for (i = 0; i < 12; i++)
        for(j = 0; j < 12; j++)
            scanf("%f", &x[i][j]);

    for(i = 0; i < 12; i++)
        soma += x[y][i];

    if (strcmp(o,"S") == 0) printf("%.1f\n", soma);
    else printf("%.1f\n", soma/12);

    return 0;
}
