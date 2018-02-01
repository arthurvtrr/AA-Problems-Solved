#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <set>

using namespace std;

#define INF 1000000000000LL

int t, n, m, nxt[330];
long long cost[330][330], tax[330];

int main() {
    for (int i = 1; i < 330; i++)
        tax[i] = i*i;

    long long acum = 0;
    for (int i = 1; i < 330; i++) {
        tax[i] -= acum;
        acum += tax[i];
    }

    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%lld", &cost[i][j]);

        long long sol = 0;

        for (int i = 0; i < n; i++) {
            sort(cost[i], cost[i] + m);
            cost[i][m] = INF;
            nxt[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            long long mini = i;
            for (int j = 0; j <= i; j++)
                if (cost[j][nxt[j]] + tax[nxt[j]+1] < cost[mini][nxt[mini]] + tax[nxt[mini]+1])
                    mini = j;
            sol += cost[mini][nxt[mini]] + tax[nxt[mini]+1];
            nxt[mini]++;
        }

        printf("Case #%d: %lld\n", tc+1, sol);
    }

    return 0;
}
