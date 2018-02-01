#include <bits/stdc++.h>
using namespace std;

#define N 100100

int n, m, r, x, y;
vector < int > auxg[N], graph[N];

struct DominatorTree {
    int cnt, pos[N], best[N], p[N], parent[N], order[N];
    int link[N], idom[N], sdom[N];
    vector < int > radj[N], bucket[N];

    void dfs(int nd) {
        pos[nd] = cnt;
        order[cnt++] = nd;
        for(int ch : graph[nd])
            if(pos[ch] == -1) {
                dfs(ch);
                parent[ch] = nd;
            }
    }

    int findBest(int x) {
        if(p[x] != x) {
            int u = findBest(p[x]);
            if (pos[sdom[u]] < pos[sdom[best[x]]])
                best[x] = u;
            p[x] = p[p[x]];
        }
        return best[x];
    }

    void dominators(int n, int root) {
        cnt = 0;

        for(int i = 0; i < n+1; i++) {
            pos[i] = parent[i] = idom[i] = -1;
            p[i] = best[i] = sdom[i] = i;
        }

        for(int i = 0; i < n+1; i++)
            for(int u : graph[i])
                radj[u].push_back(i);

        dfs(root);
        for(int i = cnt-1; i >= 1; i--){
            int w = order[i];
            for(int u : radj[w])
                if(pos[u] != -1) {
                    int t = findBest(u);
                    if(pos[sdom[t]] < pos[sdom[w]])
                        sdom[w] = sdom[t];
                }

            bucket[sdom[w]].push_back(w);
            idom[w] = sdom[w];
            int pw = parent[w];
            for(int u : bucket[pw])
                link[u] = findBest(u);
            bucket[pw].clear();
            p[w] = pw;
        }

        for(int i = 1; i < cnt; i++){
            int u = order[i];
            idom[u] = idom[link[u]];
        }

        for(int i = 0; i < n+1; i++)
            radj[i].clear();
   }
} DT;

#define pii pair < int, int >
vector < pii > edges;
bool visited[N];

void dfs(int u) {
    visited[u] = true;
    for (int v : auxg[u])
        if (!visited[v])
            dfs(v);
}

int jd[N][20];
vector < int > need[N];

int main() {
    scanf("%d %d %d", &n, &m, &r);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        auxg[x].push_back(y);
        edges.push_back(pii(x, y));
    }

    dfs(r);
    for (int i = 0; i < m; i++)
        if (visited[edges[i].first] && visited[edges[i].second]) {
            graph[edges[i].first].push_back(edges[i].second);
            need[edges[i].second].push_back(edges[i].first);
        }

    DT.dominators(n+1, r);
    for (int i = 0; i < N; i++)
        if (DT.idom[i] < 1)
            DT.idom[i] = 0;

    for (int i = 1; i <= n; i++)
        jd[i][0] = DT.idom[i];

    for (int i = 1; i < 20; i++)
        for (int j = 1; j <= n; j++)
            jd[j][i] = jd[jd[j][i-1]][i-1];

    vector < int > ret;

    for (int i = 0; i < m; i++) {
        if (!visited[edges[i].first] || !visited[edges[i].second]) {
            ret.push_back(i+1);
            continue;
        }

        bool valid = false;
        if (DT.idom[edges[i].second] == edges[i].first) {
            int num = 0;
            for (int v : need[edges[i].second]) {
                if (v == edges[i].first) continue;
                int aux = v;

                for (int j = 19; j >= 0; j--)
                    if (DT.pos[jd[aux][j]] > DT.pos[edges[i].first])
                        aux = jd[aux][j];

                if (aux != edges[i].second) num++;;
            }
            if (num == 0) valid = true;
        }

        if (!valid) ret.push_back(i+1);
    }

    printf("%d\n", ret.size());
    for (int i = 0; i < ret.size(); i++) {
        if (i) printf(" ");
        printf("%d", ret[i]);
    }
    printf("\n");

    return 0;
}
