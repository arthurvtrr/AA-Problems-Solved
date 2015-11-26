#include <stdio.h>
#include <algorithm>

#define INF 1000000000

using namespace std;

void warshall(int graph[][25], int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (i != k && graph[i][k] < INF)
                for (int j = 0; j < n; j++)
                    if (graph[i][j] > graph[i][k] + graph[k][j])
                        graph[i][j] = graph[i][k] + graph[k][j];
}


int main() {
    int n, x, y, a, b, countries[25][25], c = 0;

    while (scanf("%d", &x) != EOF) {
        for (int i = 0; i < 25; i++)
            for (int j = 0; j < 25; j++)
                countries[i][j] = i != j? INF : 0;

        for (int i = 0; i < x; i++) {
            scanf("%d", &y);
            countries[1][y] = 1, countries[y][1] = 1;
        }
        for (int i = 0; i < 18; i++) {
            scanf("%d", &x);
            for (int j = 0; j < x; j++) {
                scanf("%d", &y);
                countries[i+2][y] = 1, countries[y][i+2] = 1;
            }
        }

        warshall(countries, 25);

        printf("Test Set #%d\n", ++c);

        scanf("%d", &x);
        for (int i = 0; i < x; i++) {
            scanf("%d %d", &a, &b);
            printf("%2d to %2d: %d\n", a, b, countries[a][b]);
        }
        printf("\n");
    }
    return 0;
}
