#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000
#define N 500
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

int t, n, e, b, x, y, cont, supply[N], energy[N];

vector < int > aux[N], regions;
bool visited[N];
int disc[N], low[N], parent[N], reg;
vector < pii > st;
set < int > region[N*N];

void BCCUtil(int u) {
    disc[u] = low[u] = ++cont;
    int children = 0;

    for (int i = 0; i < aux[u].size(); i++) {
        int v = aux[u][i];
        if (disc[v] == -1) {
            children++;
            parent[v] = u;
            st.push_back(make_pair(u, v));
            BCCUtil(v);

            low[u] = min(low[u], low[v]);

            if((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
                while(st.back().first != u || st.back().second != v) {
                    region[reg].insert(st.back().first);
                    region[reg].insert(st.back().second);
                    st.pop_back();
                }
                region[reg].insert(st.back().first);
                region[reg].insert(st.back().second);
                st.pop_back();
                reg++;
            }
        }
        else if(v != parent[u] && disc[v] < low[u]) {
            low[u] = min(low[u], disc[v]);
            st.push_back(make_pair(u, v));
        }
    }
}

void BCC() {
    for (int i = 0; i < N; i++)
        disc[i] = low[i] = parent[i] = -1;

    reg = 0, cont = 0;
    for (int i = 0; i < N; i++) {
        if (disc[i] == -1)
            BCCUtil(i);

        bool next = false;
        while(!st.empty()) {
            next = true;
            region[reg].insert(st.back().first);
            region[reg].insert(st.back().second);
            st.pop_back();
        }

        if (next) reg++;
    }
}

#define source 115
#define sink 116

int main() {
	scanf("%d", &t);
	for (int tc = 0; tc < t; tc++) {

		for (int i = 0; i < N; i++) {
			aux[i].clear();
			visited[i] = false;
		}
		for (int i = 0; i < N*N; i++)
            region[i].clear();

		scanf("%d %d %d", &n, &e, &b);
		for (int i = 1; i <= n; i++)
			scanf("%d", &supply[i]);
		for (int i = 1; i <= b; i++)
			scanf("%d", &energy[i]);

		for (int i = 0; i < e; i++) {
			scanf("%d %d", &x, &y);
			aux[x].push_back(y);
			aux[y].push_back(x);
		}

        regions.clear();
        BCC();

        for (int i = 0; i < reg; i++)
            if (region[i].size() > 2) {
                int sum = 0;
                for (set < int >::iterator it = region[i].begin(); it != region[i].end(); it++) {
                    sum += supply[*it];
                    visited[*it] = true;
                }
                regions.push_back(sum);
            }

        for (int i = 1; i <= n; i++)
            if (!visited[i])
                regions.push_back(supply[i]);

        if (regions.size() > b) printf("Buzz Mission %d: %d No\n", tc+1, regions.size());
        else {
            int ini = 0, fim = 1000000;
            while (ini <= fim) {
                int meio = (ini + fim) / 2;

                for (int i = 0; i < N; i++)
                    graph[i].clear();

                for (int i = 1; i <= b; i++)
                    addEdge(source, i, 1);
                for (int i = 0; i < regions.size(); i++)
                    addEdge(i+60, sink, 1);
                for (int i = 1; i <= b; i++)
                    for (int j = 0; j < regions.size(); j++)
                        if (abs(regions[j]-energy[i]) <= meio)
                            addEdge(i, j+60, 1);

                if (flow(source, sink) < regions.size()) ini = meio + 1;
                else fim = meio - 1;
            }

            printf("Buzz Mission %d: %d %d\n", tc+1, regions.size(), ini);
        }
	}

	return 0;
}

/*
10000
5 6 3
1 6 7 2 6
1 8 6
1 2
2 3
3 1
3 4
4 5
5 3

10 12 6
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1
1 2
2 3
3 1
3 4
4 5
5 3
4 6
3 7
3 8
7 9
8 9
9 10
*/
