#include <stdio.h>

using namespace std;

int main() {
    int n, mat[220][220], x, y, cont[1100];
    for (int i = 0; i < 1100; i++) cont[i] = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &mat[i][j]);
    for (int i = 0; i < 2*n; i++) {
        scanf("%d %d", &x, &y);
        cont[mat[x][y]]++;
    }
    int sol = 0;
    for (int i = 0; i < 1001; i++)
        if (cont[i] > 0) sol++;

    printf("%d\n", sol);
    return 0;
}

