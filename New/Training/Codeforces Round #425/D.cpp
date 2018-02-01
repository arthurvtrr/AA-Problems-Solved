#include <bits/stdc++.h>

using namespace std;

#define MAX 100100
#define LOG 20

int n, q, x, pos[3];
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
      int timp, log;

      if (L[p] < L[q])
          timp = p, p = q, q = timp;

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

int dst(int a, int b) {
    return L[a] + L[b] - 2*L[lca(a, b)];
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &x);
        graph[x].push_back(i);
        graph[i].push_back(x);
    }

    dfs(1, 0, 1);
    process(MAX);

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &pos[0], &pos[1], &pos[2]);
        int ans = 0;
        for (int j = 0; j < 3; j++) {
            vector < int > lft;
            for (int k = 0; k < 3; k++)
                if (k != j)
                    lft.push_back(k);

            ans = max(ans, (dst(pos[j], pos[lft[0]]) + dst(pos[j], pos[lft[1]]) - dst(pos[lft[0]], pos[lft[1]])) / 2 + 1);
        }
        printf("%d\n", ans);
    }

    return 0;
}
