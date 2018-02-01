#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000
#define pii pair < int, int >

int n, k1, k2, x;
vector < int > s[2];

short dp[7005][2];

short solve(int id, int p) {
    if (dp[id][p] != -1)
        return dp[id][p];

    for (int i = 0; i < s[p].size(); i++)
        if ((id + s[p][i]) % n == 0)
            return dp[id][p] = 1;

    short ret = 0;

    for (int i = 0; i < s[p].size(); i++) {
        short aux = solve((id + s[p][i]) % n, 1 - p);
        if (aux == 0) ret = 1;
    }

    return dp[id][p] = ret;
}

int dist[7005][2];

void bfs(int ini, int p) {
    for (int i = 0; i < 7005; i++)
        dist[i][0] = dist[i][1] = INF;

    queue < pii > fila;
    fila.push(pii(ini, p));
    dist[ini][p] = 0;

    while (!fila.empty()) {
        pii u = fila.front();
        fila.pop();

        for (int i = 0; i < s[u.second].size(); i++)
            if (dist[(u.first + s[u.second][i]) % n][1 - u.second] > dist[u.first][u.second] + 1) {
                dist[(u.first + s[u.second][i]) % n][1 - u.second] = dist[u.first][u.second] + 1;
                fila.push(pii((u.first + s[u.second][i]) % n, 1 - u.second));
            }
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d", &k1);

    for (int i = 0; i < k1; i++) {
        scanf("%d", &x);
        s[0].push_back(x);
    }
    scanf("%d", &k2);
    for (int i = 0; i < k2; i++) {
        scanf("%d", &x);
        s[1].push_back(x);
    }

    for (int i = 0; i < 7005; i++)
        dp[i][0] = dp[i][1] = -1;

    for (int i = 1; i < n; i++) {
        if (i > 1) printf(" ");

        bfs(i, 0);
        if (dist[0][0] == INF && dist[0][1] == INF) {
            printf("Loop");
            continue;
        }

        short aux = 0;
        if (aux == 0) printf("Lose");
        else printf("Win");
    }
    printf("\n");

    for (int i = 1; i < n; i++) {
        if (i > 1) printf(" ");

        bfs(i, 1);
        if (dist[0][0] == INF && dist[0][1] == INF) {
            printf("Loop");
            continue;
        }

        short aux = 0;
        if (aux == 0) printf("Lose");
        else printf("Win");
    }
    printf("\n");

    return 0;
}

