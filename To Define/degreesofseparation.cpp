#include <stdio.h>
#include <map>
#include <iostream>
#include <string>

#define INF 1000000000

using namespace std;

typedef map < string, int > msi;

void warshall(int graph[][60], int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (i != k && graph[i][k] < INF)
                for (int j = 0; j < n; j++)
                    graph[i][j] = graph[i][j] < graph[i][k] + graph[k][j]? graph[i][j] : graph[i][k] + graph[k][j];
}

int main() {
    int p, r, c = 0;
    string x, y;

    while (scanf("%d %d", &p, &r) && p + r != 0) {
        msi ind;
        int network[60][60];
        for (int i = 0; i < 60; i++)
            for (int j = 0; j < 60; j++)
                network[i][j] = i != j? INF : 0;
        int s = 0;
        c++;

        for (int i = 0; i < r; i++) {
            cin >> x >> y;
            if (!ind.count(x)) ind[x] = s++;
            if (!ind.count(y)) ind[y] = s++;
            network[ind[x]][ind[y]] = 1;
            network[ind[y]][ind[x]] = 1;
        }

        warshall(network, p);

        int max = -1;
        for (int i = 0; i < p; i++)
			for (int j = i + 1; j < p; j++)
                if (network[i][j] > max) max = network[i][j];

        if (max < INF) printf("Network %d: %d\n\n", c, max);
        else printf("Network %d: DISCONNECTED\n\n", c);

    }

    return 0;
}
