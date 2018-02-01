#include <bits/stdc++.h>

using namespace std;

unsigned long long s[2];
unsigned long long xorshift128plus() {
	unsigned long long x = s[0];
	const unsigned long long y = s[1];
	x ^= x << 23;
	s[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
	return s[0] = y;
}

const int MX = 1000;

int C[MX][MX];
int H[MX][MX];

#define pii pair < int, int >
#define ll long long

bool cmp(pii a, pii b) {
    return C[a.first][a.second] < C[b.first][b.second];
}

int grid[MX][MX];

struct subset {
    int parent, _rank;
} subsets[MX];

int Find(int u) {
    if (subsets[u].parent != u) subsets[u].parent = Find(subsets[u].parent);
    return subsets[u].parent;
}

void Union(int x, int y) {
    int rx = Find(x), ry = Find(y);
    if (subsets[rx]._rank > subsets[ry]._rank) subsets[ry].parent = rx;
    else if (subsets[rx]._rank < subsets[ry]._rank) subsets[rx].parent = ry;
    else {
        subsets[ry].parent = rx;
        subsets[rx]._rank++;
    }
}

int main() {
	int T;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		int n, Cmax, Hmax;
		scanf("%d %d %d", &n, &Cmax, &Hmax);
		for (int i = 0; i < n; i++) {
			C[i][i] = 0;
			scanf("%llu %llu", &s[0], &s[1]);
			for (int j = i + 1; j < n; j++) {
				C[i][j] = C[j][i] = xorshift128plus() % (Cmax + 1);
			}
		}

		for (int i = 0; i < n; i++) {
			scanf("%llu %llu", &s[0], &s[1]);
			for (int j = 0; j < n; j++) {
				H[i][j] = xorshift128plus() % (Hmax + 1);
			}
		}

		vector < pii > edges;
		for (int i = 0; i < n; i++)
            for (int j = i+1; j < n; j++)
                edges.push_back(pii(i, j));
        sort(edges.begin(), edges.end(), cmp);

        for (int i = 0; i < MX; i++)
            for (int j = 0; j < MX; j++)
                grid[i][j] = 0;

        for (int i = 0; i < MX; i++) {
            subsets[i].parent = i;
            subsets[i]._rank = 1;
        }

        for (int i = 0; i < edges.size(); i++)
            if (Find(edges[i].first) != Find(edges[i].second)) {
                Union(edges[i].first, edges[i].second);
                grid[edges[i].first][edges[i].second] = grid[edges[i].second][edges[i].first] = 1;
            }

        for (int i = 0; i < MX; i++) {
            for (int j = 0; j < MX; j++)
                printf("%d", grid[i][j]);
            printf("\n");
        }
	}

	return 0;
}

