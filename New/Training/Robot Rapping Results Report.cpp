#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <queue>
#include <vector>

using namespace std;

#define pii pair < int, int >

int n, m;
pii battles[100100];

vector < int > graph[100100];
int incEdges[100100];
bool valid;

void bfs() {
    queue < int > fila;

    for (int i = 1; i <= n; i++)
        if (incEdges[i] == 0)
            fila.push(i);

    while (!fila.empty()) {
        if (fila.size() > 1) valid = false;

        int u = fila.front();
        fila.pop();

        for (int v : graph[u]) {
            incEdges[v]--;
            if (incEdges[v] == 0)
                fila.push(v);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d %d", &battles[i].first, &battles[i].second);

    int ini = 1, fim = m;

    while (ini <= fim) {
        int mid = (ini + fim) / 2;

        valid = true;
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            incEdges[i] = 0;
        }

        for (int i = 0; i < mid; i++) {
            graph[battles[i].first].push_back(battles[i].second);
            incEdges[battles[i].second]++;
        }

        bfs();

        if (valid) fim = mid-1;
        else ini = mid+1;
    }

    printf("%d\n", ini > m? -1 : ini);
    return 0;
}
