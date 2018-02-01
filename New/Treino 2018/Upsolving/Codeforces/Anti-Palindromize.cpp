#include <bits/stdc++.h>

using namespace std;

#define N 1500

int cap[N][N], cost[N][N];
int fnet[N][N], adj[N][N], deg[N];
int par[N], d[N];
int pi[N];

#define CLR(a, x) memset( a, x, sizeof( a ) )
#define Inf (INT_MAX/2)
#define Pot(u,v) (d[u] + pi[u] - pi[v])

bool dijkstra(int n, int s, int t) {
    for (int i = 0; i < n; i++) d[i] = Inf, par[i] = -1;
    d[s] = 0;
    par[s] = -n - 1;

    while (1) {
        int u = -1, bestD = Inf;
        for (int i = 0; i < n; i++)
            if (par[i] < 0 && d[i] < bestD)
                bestD = d[u = i];

        if (bestD == Inf) break;

        par[u] = -par[u] - 1;
        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];
            if (par[v] >= 0) continue;
            if (fnet[v][u] && d[v] > Pot(u, v) - cost[v][u])
                d[v] = Pot(u, v) - cost[v][u], par[v] = -u-1;

            if (fnet[u][v] < cap[u][v] && d[v] > Pot(u, v) + cost[u][v])
                d[v] = Pot(u, v) + cost[u][v], par[v] = -u - 1;
        }
    }

    for (int i = 0; i < n; i++)
        if (pi[i] < Inf)
            pi[i] += d[i];

    return par[t] >= 0;
}

int mcmf(int n, int s, int t, int &fcost) {
    CLR(deg, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (cap[i][j] || cap[j][i])
                adj[i][deg[i]++] = j;

    CLR(fnet, 0);
    CLR(pi, 0);
    int flow = fcost = 0;

    while (dijkstra(n, s, t)) {
        int bot = INT_MAX;
        for (int v = t, u = par[v]; v != s; u = par[v = u])
            bot = min(bot, fnet[v][u] ? fnet[v][u] : (cap[u][v] - fnet[u][v]));

        for (int v = t, u = par[v]; v != s; u = par[v = u])
            if (fnet[v][u]) { fnet[v][u] -= bot; fcost -= bot * cost[v][u]; }
            else { fnet[u][v] += bot; fcost += bot * cost[u][v]; }

        flow += bot;
    }

    return flow;
}

int n, nums[110], cnt[30];
string s;

#define source 1497
#define sink 1498

int main() {
    scanf("%d", &n);
    cin >> s;
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < n; i++)
        cnt[s[i] - 'a']++;

    for (int i = 0; i < 26; i++)
        cap[source][i] = cnt[i];

    for (int i = 26; i < 26+n; i++)
        cap[i][sink] = 1;

    int pos = 26+n;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < n/2; j++) {
            cap[i][pos] = 1;
            cap[pos][26+j] = 1;
            if (i != (s[j] - 'a')) cost[pos][26+j] = nums[j];
            cap[pos][26+n-j-1] = 1;
            if (i != (s[n-j-1] - 'a')) cost[pos][26+n-j-1] = nums[n-j-1];
            pos++;
        }
    }

    int fcost;
    int flow = mcmf(N-1, source, sink, fcost);

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += nums[i];

    printf("%d\n", sum - fcost);

    return 0;
}
