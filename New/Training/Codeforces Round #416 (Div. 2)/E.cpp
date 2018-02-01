#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, m, q, x, y;
int grid[11][100010], pos[11][100010], invx[1110000], invy[1110000];

struct subset {
    int rank, parent;
} subsets[19][11][100010];

int Find(int lvl, int i, int j) {
    if (subsets[lvl][i][j].parent != pos[i][j])
        subsets[lvl][i][j].parent = Find(lvl, invx[subsets[lvl][i][j].parent], invy[subsets[lvl][i][j].parent]);
    return subsets[lvl][i][j].parent;
}

void Union(int lvl, int x1, int y1, int x2, int y2) {
    int xroot = Find(lvl, x1, y1);
    int yroot = Find(lvl, x2, y2);

    if (subsets[lvl][invx[xroot]][invy[xroot]].rank < subsets[lvl][invx[yroot]][invy[yroot]].rank)
        subsets[lvl][invx[xroot]][invy[xroot]].parent = yroot;
    else if (subsets[lvl][invx[xroot]][invy[xroot]].rank > subsets[lvl][invx[yroot]][invy[yroot]].rank)
        subsets[lvl][invx[yroot]][invy[yroot]].parent = xroot;
    else {
        subsets[lvl][invx[yroot]][invy[yroot]].parent = xroot;
        subsets[lvl][invx[xroot]][invy[xroot]].rank++;
    }
}

pii seg[400040];
int level[100010];

void setLevel(int id, int ini, int fim, int lvl) {
    if (ini == fim) {
        seg[id].second = lvl;
        level[ini] = lvl;
        return;
    }
    int meio = (ini + fim) / 2;

    seg[id].second = lvl;
    setLevel(2*id, ini, meio, lvl+1);
    setLevel(2*id+1, meio+1, fim, lvl+1);
}

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].first = n;
        for (int i = 1; i <= n-1; i++) {
            int x = Find(seg[id].second, i, ini), y = Find(seg[id].second, i+1, ini);
            if (x != y && grid[i][ini] == grid[i+1][ini]) {
                Union(seg[id].second, i, ini, i+1, ini);
                seg[id].first--;
            }
        }
        printf("%d %d %d\n", ini, fim, seg[id].first);
        return;
    }
    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id].first = seg[2*id].first + seg[2*id+1].first;

    for (int i = 1; i <= n; i++)
        for (int j = ini; j <= fim; j++)
            subsets[seg[id].second][i][j] = subsets[seg[id].second+1][i][j];

    for (int i = 1; i <= n; i++) {
        int x = Find(seg[id].second, i, meio), y = Find(seg[id].second, i, meio+1);
        if (x != y && grid[i][meio] == grid[i][meio+1]) {
            Union(seg[id].second, i, meio, i, meio+1);
            seg[id].first--;
        }
    }
    printf("%d %d %d\n", ini, fim, seg[id].first);
}

int query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id].first;

    int meio = (ini + fim) / 2;
    int ret = query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end);

    for (int i = 1; i <= n; i++)
        for (int j = ini; j <= fim; j++)
            subsets[seg[id].second][i][j] = subsets[seg[id].second+1][i][j];

    for (int i = 1; i <= n; i++) {
        int x = Find(seg[id].second, i, meio), y = Find(seg[id].second, i, meio+1);
        if (x != y && grid[i][meio] == grid[i][meio+1]) {
            Union(seg[id].second, i, meio, i, meio+1);
            ret--;
        }
    }

	return ret;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &grid[i][j]);

    setLevel(1, 1, m, 0);

    int cont = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            subsets[level[j]][i][j].parent = cont;
            invx[cont] = i; invy[cont] = j;
            pos[i][j] = cont++;
            subsets[level[j]][i][j].rank = 1;
        }

    build(1, 1, m);

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);
        printf("%d\n", query(1, 1, m, x, y));
    }

    return 0;
}

