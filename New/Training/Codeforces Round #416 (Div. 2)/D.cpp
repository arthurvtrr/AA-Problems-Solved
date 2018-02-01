#include <bits/stdc++.h>

using namespace std;

#define INF 100000000
#define pii pair < int, int >

int n, m, fx, fy, dist[110][110];
char grid[110][110];
pii prv[110][110], nxt[110][110];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool valid(int a, int b) {
    if (a < 1 || a > n) return false;
    if (b < 1 || b > m) return false;
    if (grid[a][b] == '*') return false;
    return true;
}

void bfs() {
    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 110; j++) {
            dist[i][j] = INF;
            prv[i][j] = nxt[i][j] = pii(0, 0);
        }

    queue < pii > fila;
    dist[1][1] = 0;
    fila.push(pii(1, 1));

    while (!fila.empty()) {
        pii u = fila.front();
        fila.pop();

        for (int i = 0; i < 4; i++)
            if (valid(u.first + dx[i], u.second + dy[i]) &&
                dist[u.first + dx[i]][u.second + dy[i]] > dist[u.first][u.second] + 1) {
                dist[u.first + dx[i]][u.second + dy[i]] = dist[u.first][u.second] + 1;
                fila.push(pii(u.first + dx[i], u.second + dy[i]));
                prv[u.first + dx[i]][u.second + dy[i]] = u;
            }
    }

    pii aux = pii(fx, fy);
    while (prv[aux.first][aux.second] != pii(0, 0)) {
        nxt[prv[aux.first][aux.second].first][prv[aux.first][aux.second].second] = aux;
        aux = prv[aux.first][aux.second];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'F') { fx = i; fy = j; }
        }

    bfs();

    int invU = -1, invL = -1, posx = 1, posy = 1;
    while (1) {
        if (posx == fx && posy == fy) exit(0);

        if (posx == 1 && nxt[posx][posy].first > posx && invU == -1) {
            printf("U\n");
            fflush(stdout);
            scanf("%d %d", &posx, &posy);
            if (posx == 1) invU = 0;
            else invU = 1;
        }
        else if (posy == 1 && nxt[posx][posy].second > posy && invL == -1) {
            printf("L\n");
            fflush(stdout);
            scanf("%d %d", &posx, &posy);
            if (posy == 1) invL = 0;
            else invL = 1;
        }
        else {
            if (posx < nxt[posx][posy].first) {
                if (invU) printf("U\n");
                else printf("D\n");

                fflush(stdout);
                scanf("%d %d", &posx, &posy);
            }
            else if (posx > nxt[posx][posy].first) {
                if (invU) printf("D\n");
                else printf("U\n");

                fflush(stdout);
                scanf("%d %d", &posx, &posy);
            }
            else if (posy < nxt[posx][posy].second) {
                if (invL) printf("L\n");
                else printf("R\n");

                fflush(stdout);
                scanf("%d %d", &posx, &posy);
            }
            else {
                if (invL) printf("R\n");
                else printf("L\n");

                fflush(stdout);
                scanf("%d %d", &posx, &posy);
            }
        }
    }

    return 0;
}

