#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000

int nodes = 220, ini, fim;
int dist[220], q[220], work[220];
bool visited[220];
int nums[220];

struct Edge {
    int to, rev, flowe, cap;
};

vector < Edge > graph[220];

void addEdge(int from, int to, int cap) {
    Edge a = {to, graph[to].size(), 0, cap};
    Edge b = {from, graph[from].size(), 0, 0};
    graph[from].push_back(a);
    graph[to].push_back(b);
}

bool dinic_bfs() {
    fill(dist, dist + nodes, -1);
    dist[ini] = 0;
    int qt = 0;
    q[qt++] = ini;

    for (int qh = 0; qh < qt; qh++) {
        int u = q[qh];

        for (int i = 0; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            int v = e.to;
            if (dist[v] < 0 && e.flowe < e.cap) {
                dist[v] = dist[u] + 1;
                q[qt++] = v;
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

        if (e.cap > e.flowe) {
            int v = e.to;

            if (dist[v] == dist[u] + 1) {
                int minf = dinic_dfs(v, min(flow, e.cap - e.flowe));
                if (minf > 0) {
                    e.flowe += minf;
                    graph[v][e.rev].flowe -= minf;
                    return minf;
                }
            }
        }
    }

    return 0;
}

long long flow(int _ini, int _fim) {
    ini = _ini;
    fim = _fim;
    long long result = 0;

    while (dinic_bfs()) {
        fill(work, work + nodes, 0);
        while (int delta = dinic_dfs(ini, INT_MAX))
            result += delta;
    }

    return result;
}

bool isPrime(int num) {
	if (num % 2 == 0) return false;

	for (int i = 3; i <= sqrt(num); i += 2)
		if(num % i == 0)
			return false;

	return true;
}

#define ini 218
#define fim 219

vector < int > dfs(int u) {
    vector < int > vec;
    visited[u] = true;

    for (Edge v : graph[u]) {
        if (!visited[v.to] && nums[v.to] % 2 == 0 && v.flowe == 1) vec = dfs(v.to);
        else if (!visited[v.to] && nums[v.to] % 2 != 0 && v.flowe == -1) vec = dfs(v.to);
    }

    vec.push_back(u);
    return vec;
}

int main() {
    int n, x, nume = 0, numo = 0;
    vector < vector < int > > tables;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        nums[i] = x;
        if (x % 2 != 0) {
            numo++;
            addEdge(ini, i, 2);
        }
        else {
            nume++;
            addEdge(i, fim, 2);
        }
    }

    if (n % 2 != 0 || nume != numo) printf("Impossible\n");
    else {
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (isPrime(nums[i] + nums[j])) {
                    if (nums[i] % 2 != 0) addEdge(i, j, 1);
                    else addEdge(j, i, 1);
                }
            }
        }

        if (flow(218, 219) == n) {

            for (int i = 0; i < n; i++)
                if (!visited[i])
                    tables.push_back(dfs(i));

            printf("%d\n", tables.size());
            for (int i = 0; i < tables.size(); i++) {
                printf("%d", tables[i].size());
                for (int j = 0; j < tables[i].size(); j++)
                    printf(" %d", tables[i][j] + 1);
                printf("\n");
            }

        }
        else printf("Impossible\n");
    }

    return 0;
}
