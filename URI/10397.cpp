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
} nodes[800];

struct edge {
	node from;
	node to;
	double dist;
} edges[640000];

struct subset {
	node parent;
	int rank;
} subsets[800];

bool compare(edge x, edge y) {
	return x.dist < y.dist;
}

node find(struct subset subsets[], node i) {
    if (subsets[i.i].parent != i)
        subsets[i.i].parent = find(subsets, subsets[i.i].parent);

    return subsets[i.i].parent;
}

void Union(struct subset subsets[], node x, node y) {
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
	int n, m;
	while (scanf("%d", &n) != EOF) {
		int c = 0;

		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &nodes[i].x, &nodes[i].y);
			nodes[i].i = i;
			subsets[i].parent = nodes[i];
			subsets[i].rank = 0;
		}

		for (int i = 1; i <= n; i++) {
			for (int j = i+1; j <= n; j++) {
				edges[c].from = nodes[i];
				edges[c].to = nodes[j];
				edges[c].dist = sqrt(pow(nodes[j].x - nodes[i].x, 2) + pow(nodes[j].y - nodes[i].y, 2));
				c++;
			}
		}

		sort(edges, edges+c, compare);

		scanf("%d", &m);
		int x, y;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			Union(subsets, nodes[x], nodes[y]);
		}

		double need = 0.0;

		for (int i = 0; i < c; i++) {
			node a = find(subsets, edges[i].from);
			node b = find(subsets, edges[i].to);

			if (a != b) {
				Union(subsets, edges[i].from, edges[i].to);
				need += edges[i].dist;
			}
		}

		printf("%.2f\n", need);
	}
	return 0;
}
