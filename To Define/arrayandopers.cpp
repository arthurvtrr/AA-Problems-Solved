#include <bits/stdc++.h>

using namespace std;

#define INF 2000000000

int nodes = 110, ini, fim;
int dist[110], q[110], work[110];
int nums[110], prime[110000], divs[110], p[110];
vector < int > primes;

struct rote {
    int from;
    int to;
} rotes[110];

struct Edge {
    int to, rev, flowe, cap;
};

vector < Edge > graph[110];

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

void sieve(int n) {
    prime[0] = 1, prime[1] = 1;
    for (int i = 2; i <= n+1; i++) {
        if (prime[i] == 0) {
            for (int j = i*i; j <= n+1 && j > 0; j += i)
                prime[j] = 1;
            primes.push_back(i);
        }
    }
}

#define ini 108
#define ini 109

int main() {
    sieve(100010);
    int n, m, x, y;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < m; i++)
        scanf("%d %d", &rotes[i].from, &rotes[i].to);

    int s = 0;
    memset(p, 1, sizeof p);
    for (int i = 0; i < primes.size(); i++) {
        for (int j = 0; j < 110; j++) {
            graph[j].clear();
            divs[j] = 0;
        }

        bool f = false;
        for (int j = 1; j <= n; j++) {
            int div = 0;
            int num = nums[j];
            while (num && num % primes[i] == 0) {
                num /= primes[i];
                div++;
            }
            divs[j] = div;
            if (div) {
                p[j] = 0;
                f = true;
            }
        }

        if (!f) continue;

        for (int j = 0; j < m; j++) {
            int a = rotes[j].from, b = rotes[j].to;
            if (a % 2 == 0) swap(a, b);
            addEdge(ini, a, divs[a]);
            addEdge(b, fim, divs[b]);
            addEdge(a, b, min(divs[a], divs[b]));
        }

        s += flow(ini, fim);
    }

    for (int i = 1; i <= n; i++) {
        if (!p[i]) continue;
        for (int j = 0; j < 110; j++) {
            graph[j].clear();
            divs[j] = 0;
        }

        bool f = false;
        p[i] = 0;
        for (int j = 1; j <= n; j++) {
            int div = 0;
            int num = nums[j];
            while(num && num % nums[i] == 0) {
                div++;
                num /= nums[i];
            }
            if (div) {
                f = true;
                divs[j] = div;
            }
        }

        if (!f) continue;

        for (int j = 0; j < m; j++) {
            int a = rotes[j].from, b = rotes[j].to;
            if (a % 2 == 0) swap(a, b);
            addEdge(ini, a, divs[a]);
            addEdge(b, fim, divs[b]);
            addEdge(a, b, min(divs[a], divs[b]));
        }

        s += flow(ini, fim);
    }

    printf("%d\n", s);

    return 0;
}
