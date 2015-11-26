#include <stdio.h>
#include <algorithm>

using namespace std;

struct subset {
    int parent;
    int rank;
} subsets[220000];

struct edge {
    int from;
    int to;
    int dist;
} edges[220000];

bool compare(edge x, edge y) {
    if (x.dist < y.dist) return true;
    return false;
}

int find(subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int main() {
    int m, n;
    while (scanf("%d %d", &m, &n), n || m) {
        int total = 0, need = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].dist);
            subsets[edges[i].from].parent = edges[i].from;
            subsets[edges[i].from].rank = 0;
            subsets[edges[i].to].parent = edges[i].to;
            subsets[edges[i].to].rank = 0;
            total += edges[i].dist;
        }

        sort(edges, edges + n, compare);

        for (int i = 0; i < n; i++) {
            int x = find(subsets, edges[i].from);
            int y = find(subsets, edges[i].to);
            if (x != y) {
                Union(subsets, edges[i].from, edges[i].to);
                need += edges[i].dist;
            }
        }

        printf("%d\n", total - need);

    }

    return 0;
}
