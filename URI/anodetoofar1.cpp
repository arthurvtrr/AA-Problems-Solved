#include <stdio.h>
#include <vector>
#include <map>

#define INF 1000000000

using namespace std;

void warshall(int graph[][35], int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (i != k && graph[i][k] < INF)
                for (int j = 0; j < n; j++)
                    graph[i][j] = graph[i][j] < graph[i][k] + graph[k][j]? graph[i][j] : graph[i][k] + graph[k][j];
}

int main() {
    int n, x, y, s, ttl, cases = 1;
    while(scanf("%d", &n), n) {
        map < int, int > ind;
        int network[35][35];
        for (int i = 0; i < 35; i++)
            for (int j = 0; j < 35; j++)
                network[i][j] = i != j? INF : 0;
        int c = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            if (!ind.count(x)) ind[x] = c++;
            if (!ind.count(y)) ind[y] = c++;
            if (x != y) {
                network[ind[x]][ind[y]] = 1;
                network[ind[y]][ind[x]] = 1;
            }
        }

        vector < pair < int, int > > queries;
        while (scanf("%d %d", &s, &ttl), s || ttl) {
            if (!ind.count(s)) ind[s] = c++;
            queries.push_back(make_pair(s, ttl));
        }

        warshall(network, c);

        for (int j = 0; j < queries.size(); j++) {
            int nr = 0;
            for (int i = 0; i < c; i++)
                if (network[ind[queries[j].first]][i] > queries[j].second) nr++;
            printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n", cases++, nr, queries[j].first, queries[j].second);
        }
    }

    return 0;
}
