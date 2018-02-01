#include <bits/stdc++.h>

using namespace std;

const int N = 200100;

bool has[N];
int color[N];
int marked[N], dfs_id;
vector<int> graph[N];

bool dfs(int u) {
    if (marked[u] == 1) {
        return true;
    } else if (marked[u] == -1) {
        marked[u] = 1;
        for (int v : graph[u])
            if (dfs(v))
                return true;
        marked[u] = 2;
        return false;
    } else
        return false;
}

int in[N], max_color[N];

void bfs(int n, int k) {
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (!in[i])
            q.push(i);
        if (has[i])
            max_color[i] = color[i];
        else
            max_color[i] = k;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (!has[v])
                max_color[v] = min(max_color[v], max_color[u] - 1);
            if (max_color[v] >= max_color[u] or max_color[v] <= 0) {
                printf("-1\n");
                exit(0);
            }
            --in[v];
            if (!in[v])
                q.push(v);
        }
    }
}

set<pair<int, int> > ja;

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    set<int> available;
    for (int i = 1; i <= k; ++i)
        available.insert(i);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &color[i]);
        has[i] = color[i] > 0;
        if (available.count(color[i]))
            available.erase(color[i]);
        marked[i] = -1;
    }
    while (m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        ++in[v];
        graph[u].push_back(v);
    }
    for (int i = 0; i < n; ++i) {
        if (marked[i] == -1 and dfs(i))
            return !printf("-1\n");
        ++dfs_id;
    }
    bfs(n, k);
    vector<pair<int, int>> vertex;
    for (int i = 0; i < n; ++i)
        color[i] = max_color[i];
    for (int i = 0; i < n; ++i)
        vertex.push_back({color[i], i});
    sort(vertex.begin(), vertex.end());
    for (int i = 0; i < n; ++i) {
        int u = vertex[i].second;
        if (has[u] or available.empty()) continue;
        if (*available.begin() <= color[u]) {
            color[u] = *available.begin();
            available.erase(available.begin());
        }
    }
    if (!available.empty())
        printf("-1\n");
    else
        for (int i = 0; i < n; ++i)
            printf("%d%c", color[i], " \n"[i == n - 1]);
    return 0;
}
