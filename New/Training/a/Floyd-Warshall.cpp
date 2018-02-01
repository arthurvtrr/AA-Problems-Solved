#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define MAX 505
#define INF 2000000000

int n, m, x, y, z, graph[MAX][MAX];

void warshall(int numVertices) {
    for (int k = 1; k <= numVertices; k++)
        for (int i = 1; i <= numVertices; i++)
            if (i != k && graph[i][k] < INF)
                for (int j = 1; j <= numVertices; j++)
                    if (graph[i][j] > graph[i][k] + graph[k][j])
                        graph[i][j] = graph[i][k] + graph[k][j];
}

int main() {
    //"n" é o número de vértices, "m" é o de arestas
    scanf("%d %d", &n, &m);

    //Importante setar todas as arestas do grafo com distância infinita no começo.
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            graph[i][j] = INF;

    for (int i = 0; i < m; i++) {
        //"x" e "y" são os ids dos vértices conectados pela aresta, "z" é o peso
        scanf("%d %d %d", &x, &y, &z);
        graph[x][y] = graph[y][x] = z;
    }

    //Após usar essa função, a matriz graph terá a menor distância entre todos os vértices.
    //Distância do vértice i para o j em graph[i][j]
    warshall(n);

    return 0;
}
