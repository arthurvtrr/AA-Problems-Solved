#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n;
vector < int > graph[5050];
map < string, int > ind;
string inv[5050];
int dist[5050];

void bfs() {
    queue < int > fila;
    fila.push(0);
    dist[0] = 0;

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int v : graph[u])
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                fila.push(v);
            }
    }
}

string w[110];

int main() {
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; i++)
            cin >> w[i];

        ind.clear();
        ind[""] = 0;
        inv[0] = "";

        int cnt = 1;
        for (int i = 0; i < n; i++) {
            string x = w[i];
            for (int j = 0; j < w[i].size(); j++) {
                inv[cnt] = x;
                ind[x] = cnt++;
                x.erase(x.begin());
            }
        }

        for (int i = 0; i < cnt; i++) {
            graph[i].clear();
            dist[i] = 100000000;
        }

        for (int i = 1; i < cnt; i++) {
            for (int j = 0; j < n; j++) {
                if (w[j].size() <= inv[i].size()) {
                    if (w[j][0] == inv[i][0]) {
                        string ns = "";
                        for (int k = 1; k < inv[i].size(); k++)
                            ns += inv[i][k];
                        graph[ind[ns]].push_back(i);
                    }
                }
                else {
                    if (w[j][0] == inv[i][0]) {
                        string ns = "";
                        for (int k = 1; k < w[j].size(); k++)
                            ns += w[j][k];
                        graph[ind[ns]].push_back(i);
                    }
                }
            }
        }

        bfs();

        int ans = 100000000;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (w[i].size() >= w[j].size()) continue;

                bool v = true;
                for (int k = 0; k < w[i].size(); k++)
                    if (w[i][k] != w[j][k])
                        v = false;

                if (v) {
                    string state = "";
                    for (int k = w[i].size(); k < w[j].size(); k++)
                        state += w[j][k];
                    ans = min(ans, (int)w[i].size() + dist[ind[state]]);
                }
            }

        printf("%d\n", ans == 100000000? -1 : ans);
    }

    return 0;
}
