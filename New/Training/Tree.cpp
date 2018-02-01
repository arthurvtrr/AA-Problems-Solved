#include <bits/stdc++.h>

using namespace std;

#define MAX 100100
#define LOG 20

int t, n, par[MAX];
vector < int > graph[MAX];

int T[MAX], P[MAX][LOG], L[MAX];
bool visited[MAX];

void dfs(int u, int father, int lvl) {
    T[u] = father;
    L[u] = lvl;
    visited[u] = true;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v, u, lvl+1);
}

void process(int N) {
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

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        for (int i = 0; i < MAX; i++) {
            graph[i].clear();
            T[i] = L[i] = visited[i] = 0;
        }

        scanf("%d", &n);
        for (int i = 2; i <= n; i++) {
            scanf("%d", &par[i]);
            graph[i].push_back(par[i]);
            graph[par[i]].push_back(i);
        }

        dfs(1, 0, 1);
        process(MAX);

        int x = 1, y = 1;
        for (int i = 2; i <= n; i++) {
            int a = L[x] + L[y] - 2*L[lca(x, y)];
            int b = L[x] + L[i] - 2*L[lca(x, i)];
            int c = L[y] + L[i] - 2*L[lca(y, i)];
            if (b > a) y = i;
            else if (c > a) x = i;
            printf("%d\n", L[x] + L[y] - 2*L[lca(x, y)]);
        }
    }

    return 0;
}
