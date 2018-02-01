#include <bits/stdc++.h>

using namespace std;

#define N 100100
#define LOG 20
#define pii pair < int, int >

int n, q, x, y;
vector < int > graph[N];
int T[N], P[N][LOG], L[N];
bool visited[N];

void dfs(int u, int father, int lvl) {
    T[u] = father;
    L[u] = lvl;
    visited[u] = true;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v, u, lvl+1);
}

void process() {
      for (int i = 0; i < N; i++)
          for (int j = 0; 1 << j < N; j++)
              P[i][j] = -1;

      for (int i = 0; i < N; i++)
          P[i][0] = T[i];

      for (int j = 1; 1 << j < N; j++)
         for (int i = 0; i < N; i++)
             if (P[i][j - 1] != -1)
                 P[i][j] = P[P[i][j - 1]][j - 1];
}

int lca(int p, int q) {
      int tmp, log;

      if (L[p] < L[q])
          tmp = p, p = q, q = tmp;

      for (log = 1; 1 << log <= L[p]; log++);
      log--;

      for (int i = log; i >= 0; i--)
          if (L[p] - (1 << i) >= L[q])
              p = P[p][i];

      if (p == q)
          return p;

      for (int i = log; i >= 0; i--)
          if (P[p][i] != -1 && P[p][i] != P[q][i])
              p = P[p][i], q = P[q][i];

      return T[p];
}

int getDist(int a, int b) {
    return L[a] + L[b] - 2*L[lca(a, b)];
}

struct CentroidDec {
    int root, visited[N], siz[N], layer[N], parent[N];
    vector < int > centroidTree[N];
    set < pii > whites[N];

    void init() {
        for (int i = 0; i < N; i++) {
            visited[i] = siz[i] = layer[i] = parent[i] = 0;
            centroidTree[i].clear(); whites[i].clear();
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

    dfs(1, 0, 1);
    process();
    centroid.init();
    centroid.buildTree();

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);
        if (x) {
            int ans = N, aux = y;
            while (aux != 0) {
                int nxt = centroid.whites[aux].empty()? N : (*centroid.whites[aux].begin()).first;
                ans = min(ans, getDist(y, aux) + nxt);
                aux = centroid.parent[aux];
            }
            printf("%d\n", ans == N? -1 : ans);
        }
        else {
            int aux = y;
            while (aux != 0) {
                pii newv = pii(getDist(y, aux), y);
                if (centroid.whites[aux].count(newv)) centroid.whites[aux].erase(newv);
                else centroid.whites[aux].insert(newv);
                aux = centroid.parent[aux];
            }
        }
    }

    return 0;
}
