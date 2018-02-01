#include <bits/stdc++.h>

using namespace std;

int n, m, x, y, z, perm[10100];
int quant[10100];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &perm[i]);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        int aux = perm[z];

        for (int j = 1; j < 10100; j++)
            quant[j] = 0;
        for (int j = x; j <= y; j++)
            quant[perm[j]]++;
        for (int j = 1; j < 10100; j++)
            quant[j] += quant[j-1];

        if (quant[aux] != z - x + 1) printf("No\n");
        else printf("Yes\n");
    }

    return 0;
}

