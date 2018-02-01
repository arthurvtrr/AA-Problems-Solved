#include <bits/stdc++.h>

using namespace std;

#define N 200200

struct change {
    int x, y, z;
};

vector < change > ans;

int n, x, y;
vector < int > graph[N];

struct CentroidDec {
    int root, visited[N], siz[N], layer[N], parent[N];
    vector < int > centroidTree[N];

    void init() {
        for (int i = 0; i < N; i++) {
            visited[i] = siz[i] = layer[i] = parent[i] = 0;
            centroidTree[i].clear();
        }
    }

    int getCentroid(int u, int p = 0) {
        siz[u] = 1;
        for (int v : graph[u])
            if (v != p && !visited[v]) {
                getCentroid(v, u);
                siz[u] += siz[v];
            }
        if (p) return 0;

        int par = 0, aux = u, nxt = 0;
        while (1) {
            for (int v : graph[aux])
                if (!visited[v] && v != par && siz[v] > siz[u] / 2)
                    nxt = v;

            if (!nxt) return aux;
            else { par = aux; aux = nxt; nxt = 0; }
        }
    }

    void buildTree(int u = 0) {
        if (u == 0) {
            u = root = getCentroid(1);
            visited[u] = 1; layer[u] = 1;
        }

        for (int v : graph[u])
            if (!visited[v]) {
                int x = getCentroid(v);

                if (x != v) ans.push_back((change) {u, v, x});

                visited[x] = 1; layer[x] = layer[u] + 1; parent[x] = u;
                centroidTree[u].push_back(x);
                centroidTree[x].push_back(u);
                buildTree(x);
            }
    }

} centroid;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    centroid.init();
    centroid.buildTree();

    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf("%d %d %d\n", ans[i].x, ans[i].y, ans[i].z);

    return 0;
}

