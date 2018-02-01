#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int nxt, color_siz[50050], color[10010], visited[10010], pos[10010];
vector < int > graph[10010];
vector < pii > used;
stack < int > pilha[2];

void dfs(int u, int c) {
    color_siz[color[u]]--;
    color_siz[color[c]]++;

    int aux = color[u];
    color[u] = color[c];

    for (int v : graph[u])
        if (color[v] == aux)
            dfs(v, c);
}

void connect(int x, int y) {
    if (color_siz[color[x]] < color_siz[color[y]]) dfs(x, y);
    else dfs(y, x);

    graph[x].push_back(y);
    graph[y].push_back(x);
}

void disconnect(int x, int y) {
    pilha[0].push(x);
    pilha[1].push(y);

    while (!pilha[0].empty() && !pilha[1].empty()) {
        int a = pilha[0].top(), b = pilha[1].top();
        visited[a] = visited[b] = true;
        used.push_back({a, 0});
        used.push_back({b, 1});

        while (pos[a] < graph[a].size() && (visited[graph[a][pos[a]]] || color[graph[a][pos[a]]] != color[a])) pos[a]++;
        while (pos[b] < graph[b].size() && (visited[graph[b][pos[b]]] || color[graph[b][pos[b]]] != color[b])) pos[b]++;

        if (pos[a] >= graph[a].size()) pilha[0].pop();
        else if (pos[b] >= graph[b].size()) pilha[1].pop();
        else {
            pilha[0].push(graph[a][pos[a]]);
            pilha[1].push(graph[b][pos[b]]);
        }
    }

    if (pilha[0].empty()) {
        for (pii v : used)
            if (v.second == 0) {
                color_siz[color[y]]--;
                color_siz[nxt]++;
                color[v.first] = nxt;
            }

        pilha[1] = stack <int> ();
    }
    else {
        for (pii v : used)
            if (v.second == 1) {
                color_siz[color[x]]--;
                color_siz[nxt]++;
                color[v.first] = nxt;
            }
        pilha[0] = stack <int> ();
    }

    for (pii v : used) { visited[v.first] = false; pos[v.first] = 0; }
    used.clear();
    nxt++;
}

int t, m, x, y, f[5050];
vector < pii > edges;
short cnt[10010][10010];

int main() {
    scanf("%d", &t);
    while (t--) {
        edges.clear();

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &x, &y);
            if (x > y) swap(x, y);
            edges.push_back(pii(x, y));
        }

        memset(f, 0, sizeof f);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 10010; j++) {
                color[j] = j;
                color_siz[j] = 1;
                graph[j].clear();
            }
            nxt = 10011;

            for (int j = 0; j < m; j++)
                cnt[edges[j].first][edges[j].second] = 0;

            for (int j = 0; j < i; j++) {
                if (color[edges[j].first] != color[edges[j].second] && cnt[edges[j].first][edges[j].second] == 0)
                    connect(edges[j].first, edges[j].second);
                cnt[edges[j].first][edges[j].second]++;
            }

            int aux = i+1;
            for (int j = 0; j <= i; j++) {
                while (aux < m && color[edges[i].first] != color[edges[i].second]) {
                    if (color[edges[aux].first] != color[edges[aux].second] && cnt[edges[aux].first][edges[aux].second] == 0)
                        connect(edges[aux].first, edges[aux].second);
                    cnt[edges[aux].first][edges[aux].second]++;
                    aux++;
                }

                if (color[edges[i].first] == color[edges[i].second]) f[i] += m - aux + 1;
                if (j != i) {
                    if (color[edges[j].first] == color[edges[j].second] && cnt[edges[j].first][edges[j].second] == 1)
                        disconnect(edges[j].first, edges[j].second);
                    cnt[edges[j].first][edges[j].second]--;
                }
            }
        }

        for (int i = 0; i < m; i++) {
            if (i) printf(" ");
            printf("%d", f[i]);
        }
        printf("\n");
    }

    return 0;
}
