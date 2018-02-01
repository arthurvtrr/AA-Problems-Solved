#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, id[200200];
vector < int > aux, graph[200200];

struct point {
    int x, y;
} points[200200];

bool cmp(int a, int b) {
    if (points[a].x == points[b].x)
        return points[a].y < points[b].y;
    return points[a].x < points[b].x;
}

bool visited[200200];
vector < int > vis;

void dfs(int u) {
    visited[u] = true;
    vis.push_back(u);
    for (int v : graph[u])
        if (!visited[v])
            dfs(v);
}

int main() {
    while (1) {
        scanf("%d", &n);
        if (n == -1) break;

        aux.clear();
        for (int i = 0; i < 2*n + 10; i++) {
            id[i] = 0;
            graph[i].clear();
            visited[i] = false;
        }

        for (int i = 0; i < 2*n; i += 2) {
            scanf("%d %d", &points[i].x, &points[i].y);
            scanf("%d %d", &points[i+1].x, &points[i+1].y);
            aux.push_back(i); aux.push_back(i+1);
        }
        sort(aux.begin(), aux.end(), cmp);

        int ind = 1;
        id[aux[0]] = ind;
        for (int i = 1; i < 2*n; i++) {
            if (points[aux[i]].x != points[aux[i-1]].x || points[aux[i]].y != points[aux[i-1]].y) ind++;
            id[aux[i]] = ind;
        }

        for (int i = 0; i < 2*n; i += 2) {
            graph[id[i]].push_back(id[i+1]);
            graph[id[i+1]].push_back(id[i]);
        }

        int ans = 0;
        for (int i = 1; i <= ind; i++)
            if (!visited[i]) {
                vis.clear();
                dfs(i);
                int e = 0;
                for (int v : vis)
                    e += graph[v].size();
                ans += e/2 - vis.size() + 1;
            }
        printf("%d\n", ans);
    }
    return 0;
}
