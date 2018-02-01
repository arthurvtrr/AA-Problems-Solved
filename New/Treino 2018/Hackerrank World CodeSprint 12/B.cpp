#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, a, b, c, d;
int dist[220][220], pt[220][220];
int dx[6] = {-2, -2, 0, 2, 2, 0};
int dy[6] = {-1, 1, 2, 1, -1, -2};
string typ[6] = {"UL", "UR", "R", "LR", "LL", "L"};

void bfs() {
    for (int i = 0; i < 220; i++)
        for (int j = 0; j < 220; j++) {
            dist[i][j] = 10000000;
            pt[i][j] = -1;
        }

    queue < pii > fila;
    fila.push(pii(a, b));
    dist[a][b] = 0;

    while (!fila.empty()) {
        pii u = fila.front();
        fila.pop();

        for (int i = 0; i < 6; i++) {
            if (u.first + dx[i] >= 0 && u.first + dx[i] < n && u.second + dy[i] >= 0 && u.second + dy[i] < n) {
                if (dist[u.first + dx[i]][u.second + dy[i]] > dist[u.first][u.second] + 1) {
                    dist[u.first + dx[i]][u.second + dy[i]] = dist[u.first][u.second] + 1;
                    fila.push(pii(u.first + dx[i], u.second + dy[i]));
                    pt[u.first + dx[i]][u.second + dy[i]] = i;
                }
            }
        }
    }

    if (dist[c][d] == 10000000) printf("Impossible\n");
    else {
        printf("%d\n", dist[c][d]);
        vector < string > ans;
        int x = c, y = d;
        for (int i = 0; i < dist[c][d]; i++) {
            ans.push_back(typ[pt[x][y]]);
            int aux = x;
            x -= dx[pt[x][y]];
            y -= dy[pt[aux][y]];
        }
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++) {
            if (i) printf(" ");
            cout << ans[i];
        }
        printf("\n");
    }
}

int main() {
    scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
    bfs();
    return 0;
}

