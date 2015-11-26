#include <stdio.h>

using namespace std;

#define INF 10000000

void floydWarshall(int G[][550], int n) {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            if (i != k && G[i][k] < INF)
                for (int j = 1; j <= n; j++)
                    G[i][j] = G[i][j] < G[i][k] + G[k][j]? G[i][j] : G[i][k] + G[k][j];
}

int main() {
    int n, e, x, y, h, k, o, d, graph[550][550];

    while (scanf("%d %d", &n, &e) && n + e != 0) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                graph[i][j] = i != j? INF : 0;

        for (int i = 0; i < e; i++) {
            scanf("%d %d %d", &x, &y, &h);
            graph[x][y] = h;
        }

        floydWarshall(graph, n);

        for (int i = 1; i <= n; i++)
            for (int j = i+1; j <= n; j++)
                if (graph[i][j] < INF && graph[j][i] < INF) graph[i][j] = 0, graph[j][i] = 0;

        floydWarshall(graph, n);

        scanf("%d", &k);

        for (int i = 0; i < k; i++) {
            scanf("%d %d", &o, &d);
            graph[o][d] != INF? printf("%d\n", graph[o][d]) : printf("Nao e possivel entregar a carta\n");
        }

        printf("\n");
    }

    return 0;
}
