#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000
#define N 10010

int nodes = N, ini, fim;
int dist[N], work[N];

struct Edge {
    int to, rev, used_flow, cap;
};

vector < Edge > graph[N];

void addEdge(int from, int to, int cap) {
    Edge a = {to, graph[to].size(), 0, cap};
    Edge b = {from, graph[from].size(), 0, 0};
    graph[from].push_back(a);
    graph[to].push_back(b);
}

bool dinic_bfs() {
    fill(dist, dist + nodes, -1);
    dist[ini] = 0;

    queue < int > fila;
    fila.push(ini);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        for (int i = 0; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            int v = e.to;
            if (dist[v] < 0 && e.used_flow < e.cap) {
                dist[v] = dist[u] + 1;
                fila.push(v);
            }
        }
    }

    return dist[fim] >= 0;
}

int dinic_dfs(int u, int flow) {
    if (u == fim)
        return flow;

    for (int &i = work[u]; i < graph[u].size(); i++) {
        Edge &e = graph[u][i];

        if (e.cap > e.used_flow) {
            int v = e.to;

            if (dist[v] == dist[u] + 1) {
                int minf = dinic_dfs(v, min(flow, e.cap - e.used_flow));
                if (minf > 0) {
                    e.used_flow += minf;
                    graph[v][e.rev].used_flow -= minf;
                    return minf;
                }
            }
        }
    }

    return 0;
}

int flow(int _ini, int _fim) {
    ini = _ini;
    fim = _fim;
    int result = 0;

    while (dinic_bfs()) {
        fill(work, work + nodes, 0);
        while (int delta = dinic_dfs(ini, INT_MAX))
            result += delta;
    }

    return result;
}

#define source 0
#define sink 1
#define JUMP 5000

int t, n;
string line;
vector < string > words[N];
set < string > all;
map < string , int > ind;

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {

        for (int i = 0; i < N; i++) {
            graph[i].clear();
            words[i].clear();
        }
        all.clear(); ind.clear();

        scanf("%d ", &n);
        for (int i = 0; i < n; i++) {
            getline(cin, line);

            string aux = "";
            for (int j = 0; j < line.size(); j++) {
                if (line[j] == ' ') {
                    words[i].push_back(aux);
                    aux = "";
                }
                else aux += line[j];
            }
            words[i].push_back(aux);
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < words[i].size(); j++)
                all.insert(words[i][j]);

        int cnt = n;
        for (auto s : all) {
            addEdge(cnt, cnt+JUMP, 1);
            ind[s] = cnt++;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < words[i].size(); j++) {
                addEdge(i, ind[words[i][j]], INF);
                addEdge(ind[words[i][j]]+JUMP, i, INF);
            }

        printf("Case #%d: %d\n", tc, flow(source, sink));
    }
    return 0;
}
