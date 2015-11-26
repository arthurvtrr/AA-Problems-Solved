#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

struct node {
    int x;
    int y;
    int i;

    bool operator ==(const node& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator !=(const node& rhs) const {
        return x != rhs.x || y != rhs.y;
    }

} nodes[550];

struct edge {
    node from;
    node to;
    double dist;
} edges[300000];

struct subset {
    node parent;
    int rank;
} subsets[550];

bool compare (edge x, edge y) {
    return x.dist < y.dist;
}

node find(subset subsets[], node i) {
    if (subsets[i.i].parent != i)
        subsets[i.i].parent = find(subsets, subsets[i.i].parent);

    return subsets[i.i].parent;
}

void Union(subset subsets[], node x, node y) {
    node xroot = find(subsets, x);
    node yroot = find(subsets, y);

    if (subsets[xroot.i].rank < subsets[yroot.i].rank)
        subsets[xroot.i].parent = yroot;
    else if (subsets[xroot.i].rank > subsets[yroot.i].rank)
        subsets[yroot.i].parent = xroot;
    else {
        subsets[yroot.i].parent = xroot;
        subsets[xroot.i].rank++;
    }
}

int main() {
    int n, s, p;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int c = 0;
        scanf("%d %d", &s, &p);

        for (int j = 0; j < p; j++) {
            scanf("%d %d", &nodes[j].x, &nodes[j].y);
            nodes[j].i = j;
            subsets[j].parent = nodes[j];
            subsets[j].rank = 0;
        }

        for (int j = 0; j < p; j++) {
            for (int k = j+1; k < p; k++) {
                edges[c].from = nodes[j];
                edges[c].to = nodes[k];
                edges[c].dist = sqrt(pow(nodes[k].x - nodes[j].x, 2) + pow(nodes[k].y - nodes[j].y, 2));
                c++;
            }
        }

        sort(edges, edges + c, compare);

        double d = 0.0, need = p - s;

        for (int j = 0; j < c; j++) {
            node x = find(subsets, edges[j].from);
            node y = find(subsets, edges[j].to);

            if (x != y && need > 0) {
                Union(subsets, edges[j].from, edges[j].to);
                d = edges[j].dist;
                need--;
            }
        }

        printf("%.2f\n", d);

    }

    return 0;
}

