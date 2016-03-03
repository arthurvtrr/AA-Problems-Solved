#include <stdio.h>
#include <algorithm>

using namespace std;

struct subset {
    int parent;
    int rank;
    int siz = 1;
} subsets[110000];

struct edge {
    int from;
    int to;
    int dist;
} edges[110000];

bool compare(edge x, edge y) {
    return x.dist > y.dist;
}

int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
        subsets[yroot].siz += subsets[xroot].siz;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
        subsets[xroot].siz += subsets[yroot].siz;
    }
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
        subsets[xroot].siz += subsets[yroot].siz;
    }
}

int main() {
    int n, m, vals[110000], x, y;
    double sol = 0.0;

    for (int i = 0; i < 110000; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf("%d", &vals[i+1]);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        edges[i].from = x;
        edges[i].to = y;
        if (vals[x] < vals[y]) edges[i].dist = vals[x];
        else edges[i].dist = vals[y];
    }

    sort(edges, edges+m, compare);

    for (int i = 0; i < m; i++) {
        int a = find(subsets, edges[i].from);
        int b = find(subsets, edges[i].to);

        if (a != b) {
            sol += (double)edges[i].dist * subsets[a].siz * subsets[b].siz;
            Union(subsets, edges[i].from, edges[i].to);
        }
    }

    sol /= n * (n - 1.0);
    sol *= 2.0;
    printf("%.6lf\n", sol);

    return 0;
}
