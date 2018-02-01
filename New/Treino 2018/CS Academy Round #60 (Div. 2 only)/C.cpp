#include <bits/stdc++.h>

using namespace std;

int n, m, k, x;
vector < int > nums[100100], graph[100100];

int vis[100100], ans[100100], in[100100];
vector < int > ts;

void dfs(int u) {
    vis[u] = 1;
    for (int v : graph[u]) {
        if (!vis[v]) dfs(v);
        else if (vis[v] == 1) { printf("-1\n"); exit(0); }
    }
    vis[u] = 2;
    ts.push_back(u);
}

int main() {
    scanf("%d %d %d", &n, &k, &m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &x);
            nums[i].push_back(x);
        }
    }

    for (int i = 0; i < n-1; i++) {
        bool v = false;
        for (int j = 0; j < m; j++)
            if (nums[i][j] != nums[i+1][j])
                v = true;
        if (!v) {
            printf("-1\n");
            exit(0);
        }
    }

    for (int i = 0; i < n-1; i++)
        if (nums[i][0] != nums[i+1][0]) {
            graph[nums[i][0]].push_back(nums[i+1][0]);
            in[nums[i+1][0]]++;
        }

    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n-1; i++)
            if (nums[i][j-1] == nums[i+1][j-1] && nums[i][j] != nums[i+1][j]) {
                graph[nums[i][j]].push_back(nums[i+1][j]);
                in[nums[i+1][j]]++;
            }
    }

    bool f = false;
    for (int i = 0; i < k; i++)
        if (in[i] == 0 && i != nums[0][0]) {
            ans[i] = 0;
            vis[i] = 2;
            f = true;
            break;
        }

    if (!f) {
        printf("-1\n");
        exit(0);
    }

    for (int i = 0; i < k; i++)
        if (!vis[i])
            dfs(i);

    reverse(ts.begin(), ts.end());

    for (int i = 0; i < ts.size(); i++)
        ans[ts[i]] = i+1;

    for (int i = 0; i < k; i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
