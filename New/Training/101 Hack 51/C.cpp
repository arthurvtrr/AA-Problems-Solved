#include <bits/stdc++.h>

using namespace std;

#define MAX 100100
#define LOG 20
#define ll long long

int t, n, x, y, pos[3];
vector < int > graph[MAX];
ll a, b, c;

int T[MAX], P[MAX][LOG];
ll L[MAX];
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

ll dst(int a, int b) {
    return L[a] + L[b] - 2*L[lca(a, b)];
}

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        scanf("%lld %lld %lld", &a, &b, &c);
        for (int i = 0; i < 3; i++)
            scanf("%d", &pos[i]);

        for (int i = 0; i < n-1; i++) {
            scanf("%d %d", &x, &y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        dfs(1, 0, 0);
        process(n+1);

        ll ans = (L[pos[0]] + L[pos[1]] + L[pos[2]]) * a;

        for (int i = 1; i <= n; i++) {
            ll x = L[i] * c;

            sort(pos, pos+3);
            do {
                ll eq = (dst(pos[0], i) + dst(pos[1], i) - dst(pos[0], pos[1])) / 2;
                ans = min(ans, x + eq * b + (dst(pos[0], pos[1]) + dst(pos[2], i)) * a);
            } while (next_permutation(pos, pos+3));
        }

        printf("%lld\n", ans);

        for (int i = 0; i <= n; i++) {
            graph[i].clear();
            T[i] = L[i] = visited[i] = 0;
        }
    }

    return 0;
}
