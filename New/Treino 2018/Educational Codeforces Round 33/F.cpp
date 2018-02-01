#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, r, x, y, m, nums[100100], ini[100100], fim[100100], lvl[100100];
vector < int > graph[100100];
vector < pii > aux;

int t;
bool visited[100100];

void dfs(int u, int l) {
    visited[u] = true;
    lvl[u] = l;
    aux.push_back(pii(l, nums[u]));
    ini[u] = t++;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v, l+1);
    fim[u] = t-1;
}

bool cmp(pii a, pii b) {
    return a.first < b.first;
}

struct Node {
    vector < pii > inv;
    vector < int > acum;
} seg[400400];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].inv.push_back(aux[ini-1]);
        seg[id].acum.push_back(aux[ini-1].second);
        return;
    }
    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    for (pii v : seg[2*id].inv)
        seg[id].inv.push_back(v);
    for (pii v : seg[2*id+1].inv)
        seg[id].inv.push_back(v);

    sort(seg[id].inv.begin(), seg[id].inv.end(), cmp);

    int mini = INT_MAX;
    for (int i = 0; i < seg[id].inv.size(); i++) {
        mini = min(mini, seg[id].inv[i].second);
        seg[id].acum.push_back(mini);
    }
}

int query(int id, int ini, int fim, int start, int end, int val) {
    if (start > fim || end < ini)
        return INT_MAX;
    if (ini >= start && fim <= end) {
        int a = 0, b = (int)seg[id].inv.size()-1;
        while (a <= b) {
            int meio = (a + b) / 2;
            if (seg[id].inv[meio].first <= val) a = meio+1;
            else b = meio-1;
        }
        if (b == -1) return INT_MAX;
        return seg[id].acum[b];
    }

    int meio = (ini + fim) / 2;

	return min(query(2*id, ini, meio, start, end, val), query(2*id+1, meio+1, fim, start, end, val));
}

int main() {
    scanf("%d %d", &n, &r);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    t = 1;
    dfs(r, 0);
    build(1, 1, n);

    scanf("%d", &m);
    int lst = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        int a = ((x + lst) % n) + 1, b = (y + lst) % n;
        int ans = query(1, 1, n, ini[a], fim[a], b + lvl[a]);
        printf("%d\n", ans);
        lst = ans;
    }

    return 0;
}
