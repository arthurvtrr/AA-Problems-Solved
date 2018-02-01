#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000000000000
#define N 500
#define pii pair < long long, long long >

struct Edge {
	long long to, f, cap, cost, rev;
};

vector < Edge > graph[N];

void addEdge(int s, int t, long long cap, long long cost) {
	graph[s].push_back((Edge) {t, 0, cap, cost, graph[t].size()});
	graph[t].push_back((Edge) {s, 0, 0, -cost, graph[s].size() - 1});
}

long long dist[N], prevnode[N], prevedge[N], curflow[N];
bool inqueue[N];

void bellmanFord(int s) {
	for (int i = 0; i < N; i++) {
		dist[i] = INF;
		inqueue[i] = false;
	}
	dist[s] = 0;
	curflow[s] = INF;

	queue < int > fila;
	fila.push(s);

	while (!fila.empty()) {
		int u = fila.front();
		fila.pop();
		inqueue[u] = false;

		for (int i = 0; i < graph[u].size(); i++) {
			Edge &e = graph[u][i];
			if (e.f >= e.cap) continue;
			int v = e.to;
			long long ndist = dist[u] + e.cost;
			if (dist[v] > ndist) {
				dist[v] = ndist;
				prevnode[v] = u;
				prevedge[v] = i;
				curflow[v] = min(curflow[u], e.cap - e.f);
				if (!inqueue[v]) {
					inqueue[v] = true;
					fila.push(v);
				}
			}
		}
	}
}

pii minCostFlow(int s, int t, long long maxf) {
	long long flow = 0, flowCost = 0;

	while (flow < maxf) {
		bellmanFord(s);
		if (dist[t] == INF) break;

		long long df = min(curflow[t], maxf - flow);
		flow += df;
		for (int v = t; v != s; v = prevnode[v]) {
			Edge &e = graph[prevnode[v]][prevedge[v]];
			e.f += df;
			graph[v][e.rev].f -= df;
			flowCost += df * e.cost;
		}
	}

	return make_pair(flow, flowCost);
}

int n, m;
long long d, k;

struct aresta {
    long long a, b, c;
} arestas[5050];

int main() {
	int cont = 1;
	while (scanf("%d %d", &n, &m) != EOF) {

		for (int i = 0; i < N; i++) {
			graph[i].clear();
			dist[i] = prevnode[i] = prevedge[i] = curflow[i] = 0;
		}

		for (int i = 0; i < m; i++)
			scanf("%lld %lld %lld", &arestas[i].a, &arestas[i].b, &arestas[i].c);

        scanf("%lld %lld", &d, &k);
        addEdge(111, 1, d, 0);
        for (int i = 0; i < m; i++) {
            addEdge(arestas[i].a, arestas[i].b, k, arestas[i].c);
            addEdge(arestas[i].b, arestas[i].a, k, arestas[i].c);
        }

        pii ans = minCostFlow(111, n, INF);
        if (ans.first < d) printf("Instancia %d\nimpossivel\n\n", cont++);
        else printf("Instancia %d\n%lld\n\n", cont++, ans.second);
	}

	return 0;
}

