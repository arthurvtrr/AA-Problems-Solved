#include <bits/stdc++.h>

using namespace std;

#define N 1010

int n, m, x, y;
vector < int > graph[N];

struct node {
    int u, quant, sum;
} seg[4*N];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].quant = graph[ini].size();
        seg[id].u = ini;
        return;
    }
    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    if (seg[2*id].quant >= seg[2*id+1].quant) seg[id] = seg[2*id];
    else seg[id] = seg[2*id+1];
}

void update(int id, int ini, int fim, int pos, int val, bool rem) {
    if (ini == fim) {
        if (rem) seg[id].quant = 0;
        else seg[id].quant--;
        seg[id].sum += val;
        return;
    }
    int meio = (ini + fim) / 2;

    if (pos <= meio) update(2*id, ini, meio, pos, val, rem);
    else update(2*id+1, meio+1, fim, pos, val, rem);

    if (seg[2*id].quant == seg[2*id+1].quant) {
        if (seg[2*id].sum <= seg[2*id+1].sum) seg[id] = seg[2*id];
        else seg[id] = seg[2*id+1];
    }
    else if (seg[2*id].quant > seg[2*id+1].quant) seg[id] = seg[2*id];
    else seg[id] = seg[2*id+1];
}

node query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return (node) {0, 0, 0};
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

    node a = query(2*id, ini, meio, start, end);
    node b = query(2*id+1, meio+1, fim, start, end);

	if (a.quant == b.quant) {
        if (a.sum <= b.sum) return a;
        return b;
    }
    if (a.quant > b.quant) return a;
    return b;
}

int ind[N][N], ans[100100];

int main() {
    //freopen("flights.in", "r", stdin);
    //freopen("flights.out", "w", stdout);
    while (1) {
        scanf("%d %d", &n, &m);
        if (n + m == 0) break;

        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            graph[y].push_back(x);
            ind[x][y] = ind[y][x] = i;
        }

        build(1, 1, n);

        int atual = m;
        while (1) {
            node aux = seg[1];
            if (aux.quant == 0) break;

            update(1, 1, n, aux.u, atual, true);
            vector < pair < int, int > > neigh;
            for (int v : graph[aux.u])
                if (ans[ind[aux.u][v]] == 0) {
                    node ng = query(1, 1, n, v, v);
                    neigh.push_back(make_pair(ng.sum, ng.u));
                }

            sort(neigh.begin(), neigh.end());

            for (int i = 0; i < neigh.size(); i++) {
                ans[ind[aux.u][neigh[i].second]] = atual;
                update(1, 1, n, neigh[i].second, atual, false);
                atual--;
            }
        }

        printf("Yes\n");
        for (int i = 0; i < m; i++) {
            if (i) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");

        for (int i = 1; i <= n; i++)
            graph[i].clear();
        for (int i = 0; i < 4*n; i++)
            seg[i].quant = seg[i].sum = seg[i].u = 0;
        for (int i = 0; i < m; i++)
            ans[i] = 0;
    }

    return 0;
}

/*
5 8
1 5
1 3
1 4
1 2
2 3
3 4
4 5
5 2
*/
