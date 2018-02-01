#include <bits/stdc++.h>

using namespace std;

int n, m, q, x, y, pos[500500];

struct edge {
    int a, b, c, ind;
} edges[500500];

bool cmp(edge a, edge b) {
    return a.c < b.c;
}

struct sub {
    int par, rank;
} subs[500500];

bool save;

map < int, int > parc, rankc;

int Find(int u) {
    if (subs[u].par != u) {
        if (save && !parc.count(u)) parc[u] = subs[u].par;
        subs[u].par = Find(subs[u].par);
    }
    return subs[u].par;
}

void Union(int x, int y) {
    int rx = Find(x), ry = Find(y);
    if (rx == ry) return;

    if (subs[rx].rank < subs[ry].rank) {
        if (save && !parc.count(rx)) parc[rx] = subs[rx].par;
        subs[rx].par = ry;
    }
    else if (subs[rx].rank > subs[ry].rank) {
        if (save && !parc.count(ry)) parc[ry] = subs[ry].par;
        subs[ry].par = rx;
    }
    else {
        if (save && !parc.count(ry)) parc[ry] = subs[ry].par;
        subs[ry].par = rx;
        if (save && !rankc.count(rx)) rankc[rx] = subs[rx].rank;
        subs[rx].rank++;
    }
}

vector < pair < int, vector < int > > > cost[500500];

bool cmp1(int a, int b) {
    return edges[a].c < edges[b].c;
}

bool ans[500500];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
        edges[i].ind = i;
    }

    for (int i = 1; i <= n; i++) {
        subs[i].par = i;
        subs[i].rank = 1;
    }

    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        scanf("%d", &x);
        vector < int > aux;
        for (int j = 0; j < x; j++) {
            scanf("%d", &y);
            aux.push_back(--y);
        }
        sort(aux.begin(), aux.end(), cmp1);

        int lst = 0;
        vector < int > nw;
        for (int j = 0; j < x; j++) {
            if (edges[aux[j]].c != lst) {
                if (!nw.empty()) {
                    cost[lst].push_back(make_pair(i, nw));
                    nw.clear();
                }
                lst = edges[aux[j]].c;
            }
            nw.push_back(aux[j]);
        }
        cost[lst].push_back(make_pair(i, nw));
    }

    for (int i = 0; i < q; i++)
        ans[i] = true;

    sort(edges, edges+m, cmp);

    for (int i = 0; i < m; i++)
        pos[edges[i].ind] = i;

    int ind = 0;
    for (int i = 1; i < 500500; i++) {
        if (cost[i].empty()) continue;

        save = true;
        for (int j = 0; j < cost[i].size(); j++) {
            parc.clear(); rankc.clear();
            for (int v : cost[i][j].second) {
                if (Find(edges[pos[v]].a) == Find(edges[pos[v]].b)) ans[cost[i][j].first] = false;
                else Union(edges[pos[v]].a, edges[pos[v]].b);
            }

            for (auto v : parc)
                subs[v.first].par = v.second;
            for (auto v : rankc)
                subs[v.first].rank = v.second;
        }

        save = false;
        while (ind < m && edges[ind].c == i) {
            Union(edges[ind].a, edges[ind].b);
            ind++;
        }
    }

    for (int i = 0; i < q; i++)
        printf("%s\n", ans[i]? "YES" : "NO");

    return 0;
}
