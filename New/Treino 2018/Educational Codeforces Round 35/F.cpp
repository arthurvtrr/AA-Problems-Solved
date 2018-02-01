#include <bits/stdc++.h>

using namespace std;

#define INF 100000000
#define pii pair < int, int >

int n, a, b, dout[200200];
vector < int > graph[200200];

int aux, atuald;

void dfs(int u, int p, int d) {
    if (d > atuald) {
        aux = u;
        atuald = d;
    }

    for (int v : graph[u])
        if (v != p)
            dfs(v, u, d+1);
}

int t, dist[2][200200];

void dfs1(int u, int p, int d) {
    dist[t][u] = d;
    for (int v : graph[u])
        if (v != p)
            dfs1(v, u, d+1);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
        dout[a]++; dout[b]++;
    }

    pii diam;

    aux = 1, atuald = 0;
    dfs(1, 0, 0);
    diam.first = aux;

    atuald = 0;
    dfs(aux, 0, 0);
    diam.second = aux;

    for (int i = 0; i <= n; i++)
        dist[0][i] = dist[1][i] = INF;

    t = 0;
    dfs1(diam.first, 0, 0);
    t = 1;
    dfs1(diam.second, 0, 0);

    long long ans = 0;
    vector < pii > chosen;

    deque < int > leafs;
    for (int i = 1; i <= n; i++)
        if (dout[i] == 1)
            leafs.push_back(i);

    while (leafs.size() != 2) {
        while (leafs.back() == diam.first || leafs.back() == diam.second) {
            leafs.push_front(leafs.back());
            leafs.pop_back();
        }

        int x = leafs.back();
        leafs.pop_back();

        if (dist[0][x] > dist[1][x]) {
            chosen.push_back(pii(diam.first, x));
            ans += dist[0][x];
        }
        else {
            chosen.push_back(pii(diam.second, x));
            ans += dist[1][x];
        }

        for (int v : graph[x]) {
            dout[v]--;
            if (dout[v] == 1)
                leafs.push_back(v);
        }
    }

    if (leafs[0] == diam.second) swap(leafs[0], leafs[1]);

    while (leafs.size() != 1) {
        int x = leafs[1];
        leafs.pop_back();

        chosen.push_back(pii(leafs[0], leafs[1]));
        ans += dist[0][leafs[1]];

        for (int v : graph[x]) {
            dout[v]--;
            if (dout[v] == 1)
                leafs.push_back(v);
        }
    }

    printf("%lld\n", ans);
    for (int i = 0; i < chosen.size(); i++)
        printf("%d %d %d\n", chosen[i].first, chosen[i].second, chosen[i].second);

    return 0;
}
