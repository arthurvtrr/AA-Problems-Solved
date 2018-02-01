#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>

using namespace std;

#define pii pair < int, int >
#define INF 1000000000

int n, q, rak, cak, rbk, cbk;
char mat[1010][1010], ind[1010][1010];

int distL[1010][1010], distC[1010][1010];

vector < pii > graph[1001000], mst[1001000];

bool valid(int a, int b, int c, int d) {
    if (c < 0 || c > n+1) return false;
    if (d < 0 || d > n+1) return false;
    if (c != a && distL[c][d] > distL[a][b] + 1) return true;
    if (d != b && distC[c][d] > distC[a][b] + 1) return true;
    return false;
}

void bfs() {
    for (int i = 0; i < 1010; i++)
        for (int j = 0; j < 1010; j++)
            distL[i][j] = distC[i][j] = INF;

    queue < pii > fila;

    for (int i = 0; i <= n+1; i++)
        for (int j = 0; j <= n+1; j++)
            if (mat[i][j] == '#') {
                fila.push(make_pair(i, j));
                distL[i][j] = distC[i][j] = 0;
            }

    while (!fila.empty()) {
        pii u = fila.front();
        fila.pop();

        if (valid(u.first, u.second, u.first-1, u.second)) {
            distL[u.first-1][u.second] = distL[u.first][u.second]+1;
            if (distC[u.first][u.second] != 0)
                distC[u.first-1][u.second] = min(distC[u.first-1][u.second], distC[u.first][u.second]);
            fila.push(make_pair(u.first-1, u.second));
        }
        if (valid(u.first, u.second, u.first+1, u.second)) {
            distL[u.first+1][u.second] = distL[u.first][u.second]+1;
            if (distC[u.first][u.second] != 0)
                distC[u.first+1][u.second] = min(distC[u.first+1][u.second], distC[u.first][u.second]);
            fila.push(make_pair(u.first+1, u.second));
        }
        if (valid(u.first, u.second, u.first, u.second-1)) {
            distC[u.first][u.second-1] = distC[u.first][u.second]+1;
            if (distL[u.first][u.second] != 0)
                distL[u.first][u.second-1] = min(distL[u.first][u.second-1], distL[u.first][u.second]);
            fila.push(make_pair(u.first, u.second-1));
        }
        if (valid(u.first, u.second, u.first, u.second+1)) {
            distC[u.first][u.second+1] = distC[u.first][u.second]+1;
            if (distL[u.first][u.second] != 0)
                distL[u.first][u.second+1] = min(distL[u.first][u.second+1], distL[u.first][u.second]);
            fila.push(make_pair(u.first, u.second+1));
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < 1010; i++)
        for (int j = 0; j < 1010; j++)
            mat[i][j] = '#';

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf(" %c", &mat[i][j]);

    for (int i = 0; i < 1010; i++)
        for (int j = 0; j < 1010; j++)
            ind[i][j] = (n+2)*i + j;

    bfs();

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (mat[i][j] == '.') {
                if (mat[i-1][j] == '.') {
                    int siz = 1 + (min(distL[i][j], min(distL[i-1][j], min(distC[i][j], distC[i-1][j]))) - 1) * 2;
                    graph[ind[i][j]].push_back(make_pair(ind[i-1][j], siz));
                }
                if (mat[i+1][j] == '.') {
                    int siz = 1 + (min(distL[i][j], min(distL[i+1][j], min(distC[i][j], distC[i+1][j]))) - 1) * 2;
                    graph[ind[i][j]].push_back(make_pair(ind[i+1][j], siz));
                }
                if (mat[i][j-1] == '.') {
                    int siz = 1 + (min(distL[i][j], min(distL[i][j-1], min(distC[i][j], distC[i][j-1]))) - 1) * 2;
                    graph[ind[i][j]].push_back(make_pair(ind[i][j-1], siz));
                }
                if (mat[i][j+1] == '.') {
                    int siz = 1 + (min(distL[i][j], min(distL[i][j+1], min(distC[i][j], distC[i][j+1]))) - 1) * 2;
                    graph[ind[i][j]].push_back(make_pair(ind[i][j+1], siz));
                }
            }

    for (int i = 1; i <= n; i++)
        for (pii v : graph[i]) {
            printf("%d %d %d\n", i, v.first, v.second);
        }

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d %d", &rak, &cak, &rbk, &cbk);
        // printa lca(ind[rak][cak], ind[rbk][cbk])
    }

    return 0;
}
