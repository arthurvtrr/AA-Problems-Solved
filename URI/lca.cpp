#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;

#define MAX 1010
#define LOG 10

int T[MAX], P[MAX][LOG], L[MAX];
vector < int > graph[1010];

void process(int N) {
  //we initialize every element in P with -1
      for (int i = 0; i < N; i++)
          for (int j = 0; 1 << j < N; j++)
              P[i][j] = -1;

  //the first ancestor of every node i is T[i]
      for (int i = 0; i < N; i++)
          P[i][0] = T[i];

  //bottom up dynamic programing
      for (int j = 1; 1 << j < N; j++)
         for (int i = 0; i < N; i++)
             if (P[i][j - 1] != -1)
                 P[i][j] = P[P[i][j - 1]][j - 1];
}

int query(int N, int p, int q) {
      int tmp, log;

  //if p is situated on a higher level than q then we swap them
      if (L[p] < L[q])
          tmp = p, p = q, q = tmp;

  //we compute the value of [log(L[p)]
      for (log = 1; 1 << log <= L[p]; log++);
      log--;

  //we find the ancestor of node p situated on the same level
  //with q using the values in P
      for (int i = log; i >= 0; i--)
          if (L[p] - (1 << i) >= L[q])
              p = P[p][i];

      if (p == q)
          return p;

  //we compute LCA(p, q) using the values in P
      for (int i = log; i >= 0; i--)
          if (P[p][i] != -1 && P[p][i] != P[q][i])
              p = P[p][i], q = P[q][i];

      return T[p];
}

bool visited[1010];

void dfs(int u, int f, int l) {
    T[u] = f;
    L[u] = l;
    visited[u] = true;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v, u, l+1);
}

int main() {
    int t, n, q, x, y, z;
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        memset(T, 0, sizeof T);
        memset(L, 0, sizeof L);
        memset(visited, false, sizeof visited);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            for (int j = 0; j < x; j++) {
                scanf("%d", &y);
                graph[i].push_back(y);
                graph[y].push_back(i);
            }
        }
        dfs(1, 1, 0);
        process(n+1);
        scanf("%d", &q);
        printf("Case %d:\n", tc+1);
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &x, &y);
            int sol = query(n, x, y);
            printf("%d\n", sol);
        }
    }
    return 0;
}
