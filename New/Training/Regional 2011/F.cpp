#include <bits/stdc++.h>

using namespace std;

int g, p, races[110][110], s, k, pont[110], total[110];

int main() {
    while (1) {
        scanf("%d %d", &g, &p);
        if (g + p == 0) break;

        for (int i = 0; i < g; i++)
            for (int j = 0; j < p; j++)
                scanf("%d", &races[i][j]);

        scanf("%d", &s);
        for (int st = 0; st < s; st++) {
            memset(pont, 0, sizeof pont);
            memset(total, 0, sizeof total);

            scanf("%d", &k);
            for (int j = 1; j <= k; j++)
                scanf("%d", &pont[j]);

            for (int a = 0; a < g; a++)
                for (int b = 0; b < p; b++)
                    total[b] += pont[races[a][b]];

            int maxi = 0;
            for (int i = 0; i < p; i++)
                maxi = max(maxi, total[i]);

            vector < int > champs;
            for (int i = 0; i < p; i++)
                if (total[i] == maxi)
                    champs.push_back(i+1);

            for (int i = 0; i < champs.size(); i++) {
                if (i) printf(" ");
                printf("%d", champs[i]);
            }
            printf("\n");
        }
    }
    return 0;
}

