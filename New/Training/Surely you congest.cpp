#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000
#define N 25500
#define pii pair < int, int >

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

#define source 25490
#define sink 1

int n, m, c, x, y, z, quant[N], ord[N];

struct aresta {
    int a, b, c;
} arestas[50500];

vector < pii > aux[N];
int distB[N];

void dijkstra() {
    for (int i = 0; i < N; i++)
        distB[i] = INF;

    priority_queue < pii > fila;
    fila.push(make_pair(0, 1));
    distB[1] = 0;

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        for (pii v : aux[u])
            if (distB[v.first] > distB[u] + v.second) {
                distB[v.first] = distB[u] + v.second;
                fila.push(make_pair(-distB[v.first], v.first));
            }
    }
}

bool comp(int a, int b) {
    return distB[a] < distB[b];
}

void create_graph() {
    for (int i = 0; i < m; i++) {
        int dist_a = distB[arestas[i].a], dist_b = distB[arestas[i].b];
        if (dist_a == dist_b + arestas[i].c)
            addEdge(arestas[i].a, arestas[i].b, 1);
        if (dist_b == dist_a + arestas[i].c)
            addEdge(arestas[i].b, arestas[i].a, 1);
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        aux[x].push_back(make_pair(y, z));
        aux[y].push_back(make_pair(x, z));
        arestas[i].a = x; arestas[i].b = y; arestas[i].c = z;
    }

    for (int i = 0; i < c; i++) {
        scanf("%d", &x);
        quant[x]++;
    }

    dijkstra();

    for (int i = 0; i < N; i++)
        ord[i] = i+1;
    sort(ord, ord+n, comp);
    distB[n+1] = -1;

    int sol = 0, pos = 0, last = 0;
    while (pos < n) {
        if (distB[ord[pos]] != distB[ord[pos+1]]) {
            bool valid = false;
            for (int i = last; i <= pos; i++)
                if (quant[ord[i]] > 0)
                    valid = true;

            if (valid) {
                for (int i = 0; i < N; i++)
                    graph[i].clear();
                create_graph();
                for (int i = last; i <= pos; i++)
                    if (quant[ord[i]] > 0)
                        addEdge(source, ord[i], quant[ord[i]]);

                sol += flow(source, sink);
            }

            last = pos+1;
        }
        pos++;
    }

    printf("%d\n", sol);
	return 0;
}
