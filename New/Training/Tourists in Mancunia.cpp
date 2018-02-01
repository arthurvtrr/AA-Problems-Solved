#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, e, x, y;
bool visited[100100];
vector < pii > edges, graph[100100];
set < pii > found;
list < int > cyc;

void dfs(int u) {
    visited[u] = true;
    for (pii v : graph[u])
        if (!visited[v.first])
            dfs(v.first);
}

void eulerTour(list<int>::iterator i, int u) {
    for (int j = 0; j < graph[u].size(); j++) {
        pii& v = graph[u][j];
        if (v.second) {
            v.second = 0;
            for (int k = 0; k < graph[v.first].size(); k++) {
                pii& uu = graph[v.first][k];
                if (uu.first == u && uu.second) {
                    uu.second = 0;
                    break;
                }
            }
            eulerTour(cyc.insert(i, u), v.first);
        }
    }
}

int main() {
    scanf("%d %d", &n, &e);
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &x ,&y);
        graph[x].push_back(pii(y, 1));
        graph[y].push_back(pii(x, 1));
        edges.push_back(pii(x, y));
    }

    dfs(1);

    bool valid = true;
    for (int i = 1; i <= n; i++)
        if (graph[i].size() % 2 != 0 || !visited[i])
            valid = false;

    if (!valid) printf("NO\n");
    else {
        cyc.clear();
        eulerTour(cyc.begin(), 1);
        int last = 0;
        for (list<int>::iterator it = cyc.begin(); it != cyc.end(); it++) {
            if (last) found.insert(pii(last, *it));
            last = *it;
        }
        found.insert(pii(last, *cyc.begin()));

        printf("YES\n");
        for (int i = 0; i < e; i++) {
            if (found.count(edges[i])) printf("%d %d\n", edges[i].first, edges[i].second);
            else printf("%d %d\n", edges[i].second, edges[i].first);
        }
    }

    return 0;
}
