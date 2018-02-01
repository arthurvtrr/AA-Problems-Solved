#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n;
vector < pii > graph[5050];
map < string, int > ind;
string inv[5050];
int dist[5050];

void dijkstra() {
    priority_queue < pii > fila;
    fila.push(pii(0, 0));
    dist[0] = 0;

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        for (pii v : graph[u])
            if (dist[v.first] > dist[u] + v.second) {
                dist[v.first] = dist[u] + v.second;
                fila.push(pii(-dist[v.first], v.first));
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

        for (int i = 0; i < 5050; i++) {
            graph[i].clear();
            dist[i] = 100000000;
        }

        int cnt = 1;
        for (int i = 0; i < n; i++) {
            string x = w[i];
            for (int j = 0; j < w[i].size(); j++) {
                inv[cnt] = x;
                ind[x] = cnt++;

                bool v = true;
                for (int k = 0; k < x.size(); k++)
                    if (x[k] != w[i][k])
                        v = false;

                if (v) {
                    string ns = "";
                    for (int k = x.size(); k < w[i].size(); k++)
                        ns += w[i][k];
                    graph[ind[ns]].push_back(pii(ind[x], j+1));
                    printf("%d %d %d\n", ind[ns], ind[x], j+1);
                }

                x.erase(x.begin());
            }
        }

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
                    graph[ind[state]].push_back(pii(ind[w[j]], w[i].size()));
                    printf("%d %d %d\n", ind[state], ind[w[j]], w[i].size());
                }
            }

        dijkstra();

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
