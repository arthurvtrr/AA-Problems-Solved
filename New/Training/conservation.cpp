#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>

using namespace std;

int t, n, m, lab[100100], parents[100100], copyP[100100], x, y, cont, type;
vector < int > graph[100100], nextN, aux;
bool visited[100100];

void bfs() {
    queue < int > fila;

    for (int v : nextN)
        if (lab[v] == type)
            fila.push(v);
        else
            aux.push_back(v);

    nextN = aux;
    aux.clear();

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        visited[u] = true;
        cont++;
        parents[u]--;

        for (int v : graph[u])
            if (!visited[v] && lab[u] == lab[v]) {
                parents[v]--;
                if (parents[v] == 0)
                    fila.push(v);
            }
            else if (!visited[v]) {
                parents[v]--;
                if (parents[v] == 0)
                    nextN.push_back(v);
            }
    }
}

int main() {
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &n, &m);

		for (int i = 1; i <= n; i++) {
            parents[i] = 0;
            graph[i].clear();
            scanf("%d", &lab[i]);
        }

		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			graph[x].push_back(y);
			parents[y]++;
		}

		for (int i = 1; i <= n; i++) {
            visited[i] = false;
            copyP[i] = parents[i];

            if (parents[i] == 0)
                nextN.push_back(i);
        }

        int sol1 = -1, sol2 = -1;

        cont = 0, type = 1;
        while (cont != n) {
            bfs();
            sol1++;
            type = 3 - type;
        }

        for (int i = 1; i <= n; i++) {
            visited[i] = false;
            parents[i] = copyP[i];

            if (parents[i] == 0)
                nextN.push_back(i);
        }

        cont = 0, type = 2;
        while (cont != n) {
            bfs();
            sol2++;
            type = 3 - type;
        }

		printf("%d\n", sol1 < sol2? sol1 : sol2);
	}
	return 0;
}
