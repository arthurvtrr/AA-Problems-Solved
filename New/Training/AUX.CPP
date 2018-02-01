#include <bits/stdc++.h>

using namespace std;

#define MAX 50050
#define LOG 20

int n, q, col[MAX], x, y, z, st[MAX], et[MAX], tim;
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

void gen(int u, int p) {
    st[u] = tim++;
    aux.push_back(u);
    for (int v : graph[u])
        if (v != p)
            gen(v, u);

    et[u] = tim++;
    aux.push_back(u);
}

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

int orig[MAX], pos[MAX];
set < int > cols;
map < int, int > nw;
vector < freq > cnt;
vector < int > app[MAX];

void radixsort(vector < int > &vetor, int tamanho) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));

    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }

    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }

    free(b);
}

void fastsort(vector < freq > &cnt) {
    int maxf = 0;
    for (int i = 0; i < cnt.size(); i++)
        if (maxf < cnt[i].f)
            maxf = cnt[i].f;

    for (int i = 0; i < cnt.size(); i++)
        app[cnt[i].f].push_back(cnt[i].num);

    for (int i = 0; i <= maxf; i++)
        if (app[i].size())
            radixsort(app[i], app[i].size());

    cnt.clear();
    for (int i = maxf; i >= 0; i--)
        for (int j = (int)app[i].size() - 1; j >= 0; j--)
            cnt.push_back(freq(i, app[i][j]));

    for (int i = 0; i <= maxf; i++)
        app[i].clear();
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &col[i]);
        cols.insert(col[i]);
    }

    int ind = 0;
    for (auto v : cols) {
        orig[ind] = v;
        nw[v] = ind++;
    }

    for (int i = 1; i <= n; i++)
        col[i] = nw[col[i]];

    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    tim = 0;
    gen(1, 0);
    dfs(1, 0, 1);
	process(MAX);

	memset(pos, -1, sizeof pos);

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &x, &y, &z);
        cnt.clear();

        if (st[x] > st[y]) swap(x, y);

        if (lca(x, y) == x) {
            for (int j = st[x]; j <= st[y]; j++) {
                if (j == st[aux[j]] && et[aux[j]] <= st[y]) j = et[aux[j]];
                else {
                    if (pos[col[aux[j]]] == -1) {
                        pos[col[aux[j]]] = cnt.size();
                        cnt.push_back(freq(1, col[aux[j]]));
                    }
                    else cnt[pos[col[aux[j]]]].f++;
                }
            }
        }
        else {
            int Lca = lca(x, y);
            if (pos[col[Lca]] == -1) {
                pos[col[Lca]] = cnt.size();
                cnt.push_back(freq(1, col[Lca]));
            }
            else cnt[pos[col[Lca]]].f++;

            for (int j = et[x]; j <= st[y]; j++) {
                if (j == st[aux[j]] && et[aux[j]] <= st[y]) j = et[aux[j]];
                else {
                    if (pos[col[aux[j]]] == -1) {
                        pos[col[aux[j]]] = cnt.size();
                        cnt.push_back(freq(1, col[aux[j]]));
                    }
                    else cnt[pos[col[aux[j]]]].f++;
                }
            }
        }

        fastsort(cnt);
        printf("%d\n", orig[cnt[z-1].num]);

        for (int j = 0; j < cnt.size(); j++)
            pos[cnt[j].num] = -1;
    }

    return 0;
}
