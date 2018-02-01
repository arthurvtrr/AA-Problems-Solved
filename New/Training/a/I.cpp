#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

int t, n, m, x, y, z, q;

struct edge {
	int from;
	int to;
	long long cost;
	int ind;
};

bool cmp(edge a, edge b) {
	return a.cost > b.cost;
}

#define pii pair < int, long long >

struct neigh {
    int to;
    int cost;
    int ind;
};

vector < edge > edges;
vector < neigh > mst[1100];

int startp[110000], firste[1000100];
bool visited[1100];

void dfs(int u) {
	visited[u] = true;

	for (neigh v : mst[u])
        if (!visited[v.to])
			dfs(v.to);
}

edge to_remove;
bool found;

void solve(int u, int used, edge aux) {
	visited[u] = true;

	for (neigh v : mst[u])
        if (!visited[v.to]) {
            if (v.cost > aux.cost) solve(v.to, v.ind, (edge) {u, v.to, v.cost, v.ind});
            else solve(v.to, v.ind, aux);
        }
        else if (v.ind != used && !found) {
            to_remove = aux;
            found = true;
        }
}

//Seg

vector < pii > seg[4000400], sizes[1000100];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = sizes[ini];

        for (int i = 0; i < (int)seg[id].size(); i++) {
            seg[id][i].second = edges[m-seg[id][i].first].cost;
            if (i > 0) seg[id][i].second += seg[id][i-1].second;
        }

        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    int a = 0, b = 0;
    while (a < (int)seg[2*id].size() && b < (int)seg[2*id+1].size()) {
        if (startp[seg[2*id][a].first] < startp[seg[2*id+1][b].first])
            seg[id].push_back(seg[2*id][a++]);
        else
            seg[id].push_back(seg[2*id+1][b++]);
    }

    while (a < (int)seg[2*id].size())
        seg[id].push_back(seg[2*id][a++]);

    while (b < (int)seg[2*id+1].size())
        seg[id].push_back(seg[2*id+1][b++]);

    for (int i = 0; i < (int)seg[id].size(); i++) {
		seg[id][i].second = edges[m-seg[id][i].first].cost;
		if (i > 0) seg[id][i].second += seg[id][i-1].second;
    }
}

long long query(int id, int ini, int fim, int start, int end, int h) {
    if (ini > end || fim < start)
        return 0;
    if (start <= ini && end >= fim) {
        int l = 0, r = seg[id].size()-1;

        while (l <= r) {
            int mid = (l + r) / 2;

            if (startp[seg[id][mid].first] >= h) r = mid-1;
            else l = mid+1;
        }

        return l == 0? 0 : seg[id][l-1].second;
    }

    int meio = (ini + fim) / 2;

    return query(2*id, ini, meio, start, end, h) + query(2*id+1, meio+1, fim, start, end, h);
}

bool cmp1(pii a, pii b) {
    return startp[a.first] < startp[b.first];
}

int main() {
	scanf("%d", &t);
	while (t--) {

        edges.clear();
		for (int i = 0; i < 1100; i++)
			mst[i].clear();

		for (int i = 0; i < 110000; i++)
			startp[i] = 0;

		for (int i = 0; i < 1000100; i++) {
			sizes[i].clear();
            firste[i] = 0;
        }

		for (int i = 0; i < 4000400; i++)
			seg[i].clear();

		scanf("%d %d", &n, &m);

		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &z);
			edges.push_back((edge) {x, y, z, 0});
		}

		sort(edges.begin(), edges.end(), cmp);

		for (int i = 0; i < m; i++)
			edges[i].ind = m-i;

        int ind = 1;
        for (int i = m-1; i >= 0; i--)
            while (ind <= edges[i].cost && ind < 1000010)
                firste[ind++] = m - i;

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < 1100; j++)
				visited[j] = false;

			dfs(edges[i].from);

			mst[edges[i].from].push_back((neigh) {edges[i].to, edges[i].cost, edges[i].ind});
			mst[edges[i].to].push_back((neigh) {edges[i].from, edges[i].cost, edges[i].ind});

			if (visited[edges[i].to]) {
				for (int j = 0; j < 1100; j++)
					visited[j] = false;
				found = false;

				solve(edges[i].from, -1, (edge) {0, 0, 0, 0});

                for (vector < neigh >::iterator it = mst[to_remove.from].begin(); it != mst[to_remove.from].end(); it++)
                    if ((*it).ind == to_remove.ind) {
                        mst[to_remove.from].erase(it);
                        break;
                    }

                for (vector < neigh >::iterator it = mst[to_remove.to].begin(); it != mst[to_remove.to].end(); it++)
                    if ((*it).ind == to_remove.ind) {
                        mst[to_remove.to].erase(it);
                        break;
                    }

				startp[to_remove.ind] = edges[i].ind;
			}
		}

		for (int i = 1; i <= m; i++)
			sizes[edges[m-i].cost].push_back(make_pair(i, 0));

		for (int i = 0; i < 1000010; i++)
			sort(sizes[i].begin(), sizes[i].end(), cmp1);

		build(1, 1, 1000010);

		scanf("%d", &q);

		int last = 0;
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &x, &y);
			long long ans = query(1, 1, 1000010, x-last, y-last, x-last < 0? 0 : firste[x-last]);
			last = ans;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
