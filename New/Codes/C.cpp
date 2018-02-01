#include <stdio.h>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

#define pii pair < int, int >
#define MAX 110000
#define LOG 17
#define piii tuple < int, int, int >

int t, n, m, x, y, z;
vector < pii > graph[MAX];
vector < piii > queries;

struct subset {
    int parent;
    int rank;
} subsets[MAX];

int _find(int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = _find(subsets[i].parent);
    return subsets[i].parent;
}

void _union(int x, int y) {
    int x_root = _find(x);
    int y_root = _find(y);

    if (subsets[x_root].rank < subsets[y_root].rank)
        subsets[x_root].parent = y_root;
    else if (subsets[x_root].rank > subsets[y_root].rank)
        subsets[y_root].parent = x_root;
    else {
        subsets[y_root].parent = x_root;
        subsets[x_root].rank++;
    }
}

int T[MAX], P[MAX][LOG], L[MAX], maxi[MAX][LOG];
bool visited[MAX];

void dfs(int u, int father, int lvl, int dist) {
    T[u] = father;
    L[u] = lvl;
    maxi[u][0] = dist;

    visited[u] = true;
    for (pii v : graph[u])
        if (!visited[v.first])
            dfs(v.first, u, lvl+1, v.second);
}

void process() {
      for (int i = 1; i <= n; i++)
          for (int j = 0; 1 << j < n; j++) {
              P[i][j] = -1;
              if (j > 0) maxi[i][j] = -1;
          }

      for (int i = 1; i <= n; i++)
          P[i][0] = T[i];

      for (int j = 1; 1 << j < n; j++)
         for (int i = 1; i <= n; i++)
             if (P[i][j - 1] != -1) {
                 P[i][j] = P[P[i][j - 1]][j - 1];
                 maxi[i][j] = max(maxi[i][j-1], maxi[P[i][j-1]][j-1]);
             }
}

int query(int p, int q) {
      int tmp, log;

      if (L[p] < L[q])
          tmp = p, p = q, q = tmp;

      for (log = 1; 1 << log <= L[p]; log++);
      log--;

      int ret = 0;

      for (int i = log; i >= 0; i--)
          if (L[p] - (1 << i) >= L[q]) {
              ret = max(ret, maxi[p][i]);
              p = P[p][i];
          }

      if (p == q)
          return ret;

      for (int i = log; i >= 0; i--)
          if (P[p][i] != -1 && P[p][i] != P[q][i]) {
              ret = max(ret, maxi[p][i]);
              ret = max(ret, maxi[q][i]);
              p = P[p][i], q = P[q][i];
          }

      return ret;
}

int main() {
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < MAX; i++) {
            graph[i].clear();
            subsets[i].parent = i;
            subsets[i].rank = 1;
            L[i] = T[i] = 0;
            visited[i] = false;
        }
        queries.clear();

        scanf("%d %d", &n, &m);

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &z);
            if (x == 1) {
                if (_find(y) != _find(z)) {
                    _union(y, z);
                    graph[y].push_back(make_pair(z, i+1));
                    graph[z].push_back(make_pair(y, i+1));
                }
            }
            else {
                queries.push_back(make_tuple(i+1, y, z));
            }
        }

        for (int i = 1; i <= n; i++)
            if (!visited[i])
                dfs(i, -1, 0, 0);
        process();

        for (int i = 0; i < queries.size(); i++) {
            if (_find(get<1>(queries[i])) != _find(get<2>(queries[i])))
                printf("-1\n");
            else {
                int time = query(get<1>(queries[i]), get<2>(queries[i]));

                if (time < get<0>(queries[i])) printf("%d\n", time);
                else printf("-1\n");
            }
        }
    }
    return 0;
}
