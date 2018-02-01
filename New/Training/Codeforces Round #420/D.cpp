#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >
#define INF 1000000000

int n, m, k, litx[10010], lity[10010];
vector < int > x[10010], y[10010], graph[10010];

bool cmp1(int a, int b) { return lity[a] < lity[b]; }
bool cmp2(int a, int b) { return litx[a] < litx[b]; }

int dist[10010][5];

void dijkstra() {
    for (int i = 0; i < 10010; i++)
        for (int j = 0; j < 5; j++)
            dist[i][j] = INF;

    priority_queue < pair < int, pii > > fila;
    fila.push(make_pair(0, pii(x[1][0], 0)));
    dist[x[1][0]][0] = 0;

    while (!fila.empty()) {
        pii u = fila.top().second;
        fila.pop();

        for (int v : graph[u.first]) {
            if (litx[u.first] == litx[v] && dist[v][u.second != 1? 0 : 1] > dist[u.first][u.second] + (v == k && u.second != 1)) {
                dist[v][u.second != 1? 0 : 1] = dist[u.first][u.second] + (v == k && u.second != 1);
                fila.push(make_pair(-dist[v][u.second != 1? 0 : 1], pii(v, u.second != 1? 0 : 1)));
            }
            else if (lity[u.first] == lity[v] && dist[v][u.second != 2? 0 : 2] > dist[u.first][u.second] + (v == k && u.second != 2)) {
                dist[v][u.second != 2? 0 : 2] = dist[u.first][u.second] + (v == k && u.second != 2);
                fila.push(make_pair(-dist[v][u.second != 2? 0 : 2], pii(v, u.second != 2? 0 : 2)));
            }
            else {
                if (abs(litx[u.first] - litx[v]) == 1 && abs(lity[u.first] - lity[v]) == 1) {
                    if (dist[v][1] > dist[u.first][u.second] + 1) {
                        dist[v][1] = dist[u.first][u.second] + 1;
                        fila.push(make_pair(-dist[v][1], pii(v, 1)));
                    }
                    if (dist[v][2] > dist[u.first][u.second] + 1) {
                        dist[v][2] = dist[u.first][u.second] + 1;
                        fila.push(make_pair(-dist[v][2], pii(v, 2)));
                    }
                }
                else if (abs(lity[u.first] - lity[v]) > 1) {
                    if (dist[v][1] > dist[u.first][u.second] + 1) {
                        dist[v][1] = dist[u.first][u.second] + 1;
                        fila.push(make_pair(-dist[v][1], pii(v, 1)));
                    }
                }
                else {
                    if (dist[v][2] > dist[u.first][u.second] + 1) {
                        dist[v][2] = dist[u.first][u.second] + 1;
                        fila.push(make_pair(-dist[v][2], pii(v, 2)));
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);

    bool found = false;
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &litx[i], &lity[i]);
        x[litx[i]].push_back(i);
        y[lity[i]].push_back(i);
        if (litx[i] == n && lity[i] == m) found = true;
    }

    if (!found) {
        litx[k] = n; lity[k] = m;
        x[n].push_back(k);
        y[m].push_back(k);
    }

    for (int i = 0; i < 10010; i++) {
        sort(x[i].begin(), x[i].end(), cmp1);
        sort(y[i].begin(), y[i].end(), cmp2);
    }

    for (int i = 0; i < k + !found; i++) {

        if (x[litx[i]-1].size()) {
            int ini = 0, fim = x[litx[i]-1].size()-1;
            while (ini <= fim) {
                int meio = (ini + fim) / 2;
                if (lity[x[litx[i]-1][meio]] <= lity[i]) ini = meio+1;
                else fim = meio-1;
            }
            graph[i].push_back(x[litx[i]-1][max(0, fim)]);
        }

        if (x[litx[i]+1].size()) {
            int ini = 0, fim = x[litx[i]+1].size()-1;
            while (ini <= fim) {
                int meio = (ini + fim) / 2;
                if (lity[x[litx[i]+1][meio]] <= lity[i]) ini = meio+1;
                else fim = meio-1;
            }
            graph[i].push_back(x[litx[i]+1][max(0, fim)]);
        }

        if (y[lity[i]-1].size()) {
            int ini = 0, fim = y[lity[i]-1].size()-1;
            while (ini <= fim) {
                int meio = (ini + fim) / 2;
                if (litx[y[lity[i]-1][meio]] <= litx[i]) ini = meio+1;
                else fim = meio-1;
            }
            graph[i].push_back(y[lity[i]-1][max(0, fim)]);
        }

        if (y[lity[i]+1].size()) {
            int ini = 0, fim = y[lity[i]+1].size()-1;
            while (ini <= fim) {
                int meio = (ini + fim) / 2;
                if (litx[y[lity[i]+1][meio]] <= litx[i]) ini = meio+1;
                else fim = meio-1;
            }
            graph[i].push_back(y[lity[i]+1][max(0, fim)]);
        }
    }

    for (int i = 0; i < k + !found; i++) {
        printf("pos %d\n", i);
        for (int j = 0; j < graph[i].size(); j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    dijkstra();

    for (int i = 0; i < k + !found; i++) {
        for (int j = 0; j <= 2; j++)
            printf("%d ", dist[i][j]);
        printf("\n");
    }

    int ans = INF;
    for (int i = 0; i < k + !found; i++)
        if (litx[i] == n && lity[i] == m)
            ans = min({ans, dist[i][0], dist[i][1], dist[i][2]});

    printf("%d\n", ans == INF? -1 : ans);

    return 0;
}

