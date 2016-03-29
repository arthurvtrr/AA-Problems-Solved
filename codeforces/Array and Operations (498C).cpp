#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 2000000000
#define N 3300

int nodes = N, ini, fim;
int dist[N], q[N], work[N];
bool visited[N];

struct Edge {
    int to, rev, flowe, cap;
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

#define ini 3098
#define fim 3099
#define MAX 60000
#define pii pair < int, int >

struct node {
    int num;
    vector < pii > factors;
} nums[110];

bool prime[MAX];
vector < int > primes;

bool gen_primes() {
    for (int i = 2; i < MAX; i++)
        prime[i] = 1;

    for (int i = 2; i < MAX; i++)
        if (prime[i]) {
            for (int j = 2*i; j < MAX; j += i)
                prime[j] = false;
            primes.push_back(i);
        }
}

bool isPrime(int x) {
    int sqr = sqrt(x);
    for (int i = 2; i <= sqr+1; i++)
        if (x % i == 0)
            return false;

    return true;
}

void calculate_factors(int n) {
    int cont = 1;
    for (int i = 0; i < n; i++) {
        if (isPrime(nums[i].num)) {
            nums[i].factors.push_back(make_pair(cont++, nums[i].num));
            continue;
        }

        int x = nums[i].num, aux = 0;
        while (x != 1) {
            while (x % primes[aux] == 0) {
                x /= primes[aux];
                nums[i].factors.push_back(make_pair(cont++, primes[aux]));
            }
            aux++;
        }
    }
}

int main() {
    int n, m, x, y;
    scanf("%d %d", &n, &m);

    gen_primes();

    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i].num);

    calculate_factors(n);

    for (int i = 0; i < n; i += 2)
        for (pii fac : nums[i].factors)
            addEdge(ini, fac.first, 1);

    for (int i = 1; i < n; i += 2)
        for (pii fac : nums[i].factors)
            addEdge(fac.first, fim, 1);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        if (x % 2 == 0) swap(x, y);

        for (pii fac1 : nums[x-1].factors)
            for (pii fac2 : nums[y-1].factors)
                if (fac1.second == fac2.second)
                    addEdge(fac1.first, fac2.first, 1);
    }

    printf("%d\n", flow(ini, fim));
    return 0;
}
