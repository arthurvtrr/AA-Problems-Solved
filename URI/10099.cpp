#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

struct subset {
    int parent;
    int rank;
} subsets[110];

struct edge {
    int from;
    int to;
    int dist;
} edges[11000];

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
    int n, r, c = 0, s, d;
    double t;

    while (scanf("%d %d", &n, &r), n || r) {
        c++;
        for (int i = 0; i <= n; i++) {
            subsets[i].parent = i;
            subsets[i].rank = 0;
        }

        for (int i = 0; i < r; i++)
            scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].dist);

        scanf("%d %d %lf", &s, &d, &t);

        sort(edges, edges+r, compare);

        double trip;


        for (int i = 0; i < r; i++) {
            int x = find(subsets, edges[i].from);
            int y = find(subsets, edges[i].to);

            if (x != y)
                Union(subsets, edges[i].from, edges[i].to);

            if (find(subsets, s) == find(subsets, d)) {
                trip = --edges[i].dist;
                break;
            }
        }

        printf("Scenario #%d\n", c);
        printf("Minimum Number of Trips = %.0f\n\n", ceil(t / trip));

    }

    return 0;
}
