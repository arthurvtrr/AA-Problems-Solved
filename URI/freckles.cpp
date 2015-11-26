#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <map>

using namespace std;

struct node {
    double x;
    double y;
    int i;

    bool operator ==(const node& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator !=(const node& rhs) const {
        return x != rhs.x || y != rhs.y;
    }

} nodes[110];

struct edge {
    node from;
    node to;
    double dist;
} edges[11000];

struct subset {
    node parent;
    int rank;
} subsets[110];

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
    int t, n;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        int c = 0;

        if (i != 0) printf("\n");
        scanf("%d", &n);

        for (int j = 0; j < n; j++) {
            scanf("%lf %lf", &nodes[j].x, &nodes[j].y);
            nodes[j].i = j;
            subsets[j].parent = nodes[j];
            subsets[j].rank = 0;
        }

        for (int j = 0; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                edges[c].from = nodes[j];
                edges[c].to = nodes[k];
                edges[c].dist = sqrt(pow(nodes[k].x - nodes[j].x, 2) + pow(nodes[k].y - nodes[j].y, 2));
                c++;
            }
        }

        sort(edges, edges + c, compare);

        double sol = 0.0;

        for (int j = 0; j < c; j++) {
            node x = find(subsets, edges[j].from);
            node y = find(subsets, edges[j].to);

            if (x != y) {
                Union(subsets, edges[j].from, edges[j].to);
                sol += edges[j].dist;
            }
        }

        printf("%.2f\n", sol);

    }

    return 0;
}
