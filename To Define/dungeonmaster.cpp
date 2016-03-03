#include <stdio.h>
#include <map>
#include <vector>
#include <queue>

#define INF 1000000000

using namespace std;

typedef pair < int, int > pii;

int bfs(char graph[][950], pii ini, pii fim, int l, int r, int c) {
    queue < pii > fila;
    map < pii, bool > visited;
    map < pii, int > dist;
    dist[ini] = 0;
    visited[ini] = true;
    fila.push(ini);

    while(!fila.empty()) {
        vector < pii > neigh;
        pii u = fila.front();
        fila.pop();

        if (u.first+1 < r && (graph[u.first+1][u.second] == '.' || graph[u.first+1][u.second] == 'E')) neigh.push_back(make_pair(u.first+1, u.second));
        if (u.first-1 >= 0 && (graph[u.first-1][u.second] == '.' || graph[u.first-1][u.second] == 'E')) neigh.push_back(make_pair(u.first-1, u.second));
        if (u.second-1 >= 0 && (graph[u.first][u.second-1] == '.' || graph[u.first][u.second-1] == 'E')) neigh.push_back(make_pair(u.first, u.second-1));
        if (u.second+1 < l*c && (graph[u.first][u.second+1] == '.' || graph[u.first][u.second+1] == 'E')) neigh.push_back(make_pair(u.first, u.second+1));
        if (u.second+c < l*c && (graph[u.first][u.second+c] == '.' || graph[u.first][u.second+c] == 'E')) neigh.push_back(make_pair(u.first, u.second+c));
        if (u.second-c >= 0 && (graph[u.first][u.second-c] == '.' || graph[u.first][u.second-c] == 'E')) neigh.push_back(make_pair(u.first, u.second-c));

        for (pii v : neigh) {
            if (!dist.count(v)) dist[v] = INF;
            if (!visited.count(v) && dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                fila.push(v);
                visited[v] = true;
            }
        }
    }

    if (!visited.count(fim) || dist[fim] >= INF) return INF;
    return dist[fim];
}

int main() {
    int l, r, c;
    while (scanf("%d %d %d%*c", &l, &r, &c), l || r || c) {
        pii ipos, fpos;
        char dungeon[35][950];

        for (int i = 0; i < l; i++) {
            for (int j = 0; j < r; j++) {
                for (int k = 0; k < c; k++) {
                    dungeon[j][i*c + k] = fgetc(stdin);
                    if (dungeon[j][i*c + k] == 'S') ipos = make_pair(j, i*c + k);
                    else if (dungeon[j][i*c + k] == 'E') fpos = make_pair(j, i*c + k);
                }
                getchar();
            }
            getchar();
        }

        int sol = bfs(dungeon, ipos, fpos, l, r, c);

        if (sol < INF) printf("Escaped in %d minute(s).\n", sol);
        else printf("Trapped!\n");

    }

    return 0;
}
