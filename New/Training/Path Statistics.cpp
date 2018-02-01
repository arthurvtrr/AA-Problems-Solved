#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T, typename cmp=less<T>> using oset =
tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

#define MAX 50050
#define LOG 20

int n, q, col[MAX], x, y, st[MAX], et[MAX], tim, dv;
vector < int > graph[MAX], aux;

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

struct query {
    int x, y, z, ind, extra = -1;
} queries[MAX];

bool cmp(query a, query b) {
    if (a.x / dv == b.x / dv) return a.y < b.y;
    return a.x / dv < b.x / dv;
}

void gen(int u, int p) {
    st[u] = tim++;
    aux.push_back(u);
    for (int v : graph[u])
        if (v != p)
            gen(v, u);

    et[u] = tim++;
    aux.push_back(u);
}

int ans[MAX];

struct freq {
    int f, num;
    freq() { f = num = 0; }
    freq(int x, int y) { f = x; num = y; }

    bool operator <(freq other) const {
        if (f == other.f)
            return num > other.num;
        return f > other.f;
    }
};

map < int, int > cnt;
oset < freq > ord;
int app[MAX];

void remove(int e) {
    int x = cnt[col[e]];
    if (x != 0) ord.erase(freq(x, col[e]));

    if (app[e] == 2) {
        cnt[col[e]]++;
        ord.insert(freq(x+1, col[e]));
    }
    else {
        cnt[col[e]]--;
        if (x-1 != 0) ord.insert(freq(x-1, col[e]));
    }
    app[e]--;
}

void add(int e) {
    int x = cnt[col[e]];
    if (x != 0) ord.erase(freq(x, col[e]));

    if (app[e] == 0) {
        cnt[col[e]]++;
        ord.insert(freq(x+1, col[e]));
    }
    else {
        cnt[col[e]]--;
        if (x-1 != 0) ord.insert(freq(x-1, col[e]));
    }
    app[e]++;
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &col[i]);

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    tim = 0;
    gen(1, 0);
    dfs(1, 0, 1);
	process(MAX);

	dv = sqrt(aux.size());

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &queries[i].x, &queries[i].y, &queries[i].z);
        queries[i].ind = i;

        if (st[queries[i].x] > st[queries[i].y])
            swap(queries[i].x, queries[i].y);

        if (lca(queries[i].x, queries[i].y) == queries[i].x) {
            queries[i].x = st[queries[i].x];
            queries[i].y = st[queries[i].y];
        }
        else {
            queries[i].extra = lca(queries[i].x, queries[i].y);
            queries[i].x = et[queries[i].x];
            queries[i].y = st[queries[i].y];
        }
    }

    sort(queries, queries+q, cmp);

    int L = 0, R = 0;
    app[aux[0]]++;
    cnt[col[aux[0]]]++;
    ord.insert(freq(1, col[aux[0]]));

    for (int i = 0; i < q; i++) {
        while (L > queries[i].x) {
            L--;
            add(aux[L]);
        }
        while (R < queries[i].y) {
            R++;
            add(aux[R]);
        }
        while (L < queries[i].x) {
            remove(aux[L]);
            L++;
        }
        while (R > queries[i].y) {
            remove(aux[R]);
            R--;
        }

        freq ret = *ord.find_by_order(queries[i].z - 1);

        if (queries[i].extra != -1) {
            int a = cnt[col[queries[i].extra]] + 1, b = col[queries[i].extra];

            if (a-1 < ret.f || (a-1 == ret.f && b < ret.num)) {
                if (a > ret.f || (a == ret.f && b > ret.num)) {
                    if (queries[i].z == 1) ret = freq(a, b);
                    else {
                        freq prv = *ord.find_by_order(queries[i].z - 2);
                        if (a < prv.f || (a == prv.f && b < prv.num)) ret = freq(a, b);
                        else ret = prv;
                    }
                }
            }
        }

        ans[queries[i].ind] = ret.num;
    }

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);

    return 0;
}
