#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>

using namespace std;

#define MAX 100100
#define INF 2000000000

int n, m, x, y, z;
vector < pair < int, int > > graph[MAX];
int dist[MAX];

void dijkstra(int ini) {
    for (int i = 0; i < MAX; i++)
        dist[i] = INF;

    priority_queue < pair < int, int > > fila;

    dist[ini] = 0;
    fila.push(make_pair(-dist[ini], ini));

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        for (pair < int, int > v : graph[u])
            if (dist[v.first] > dist[u] + v.second) {
                dist[v.first] = dist[u] + v.second;
                fila.push(make_pair(-dist[v.first], v.first));
            }
    }
}

int main() {
    //"n" é o número de vértices, "m" é o de arestas
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        //"x" e "y" são os ids dos vértices conectados pela aresta, "z" é o peso
        scanf("%d %d %d", &x, &y, &z);
        graph[x].push_back(make_pair(y, z));
        graph[y].push_back(make_pair(x, z));
    }

    //Após usar essa função, o array dist terá a menor distância entre x e todos os outros vértices.
    scanf("%d", &x);
    dijkstra(x);

    for (int i = 1; i <= n; i++)
        printf("%d\n", dist[i]);

    return 0;
}
