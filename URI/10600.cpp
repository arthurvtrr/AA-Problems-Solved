#include <stdio.h>
#include <algorithm>
#include <vector>

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
    return x.dist < y.dist;
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
    int t, n, m;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d %d", &n, &m);

        for (int j = 0; j <= n; j++) {
                subsets[j].parent = j;
                subsets[j].rank = 0;
        }

        for (int j = 0; j < m; j++)
            scanf("%d %d %d", &edges[j].from, &edges[j].to, &edges[j].dist);

        sort(edges, edges+m, compare);

        vector < int > dists, used;

        int total = 0;
        for (int j = 0; j < m; j++) {
            int x = find(subsets, edges[j].from);
            int y = find(subsets, edges[j].to);

            if (x != y) {
                Union(subsets, edges[j].from, edges[j].to);
                total += edges[j].dist;
                used.push_back(j);
            }
        }

        dists.push_back(total);

        for (int j = 0; j < used.size(); j++) {
            total = 0;
            int connected = 1;
            for (int k = 0; k <= n; k++) {
                subsets[k].parent = k;
                subsets[k].rank = 0;
            }

            for (int k = 0; k < m; k++) {
                if (k != used[j]) {
                    int x = find(subsets, edges[k].from);
                    int y = find(subsets, edges[k].to);

                    if (x != y) {
                        Union(subsets, edges[k].from, edges[k].to);
                        total += edges[k].dist;
                        connected++;
                    }
                }
            }

            if (connected == n)
                dists.push_back(total);
        }

        sort(dists.begin(), dists.end());

        printf("%d %d\n", dists[0], dists[1]);

    }

    return 0;
}

