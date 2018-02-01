#include <bits/stdc++.h>

using namespace std;

int n, m, nums[100100], x, y, counter = 1, scc = 1;

vector < int > switchs[100100], graph[200100], aux;

bool visited[200100];
int dfs_num[200100], dfs_low[200100], cp[200100];

#define JUMP 100050

void dfs(int u) {
    dfs_low[u] = dfs_num[u] = counter++;
    aux.push_back(u);
    visited[u] = true;

    for (int v : graph[u]) {
        if (!dfs_num[v])
            dfs(v);
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        while (1) {
            int v = aux.back();
            aux.pop_back();
            visited[v] = false;
            cp[v] = scc;

            if (u == v) break;
        }
        scc++;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < m; i++) {
        scanf("%d", &x);
        for (int j = 0; j < x; j++) {
            scanf("%d", &y);
            switchs[y-1].push_back(i+1);
        }
    }

    for (int i = 0; i < n; i++) {
        if (nums[i] == 1) {
            graph[switchs[i][0]].push_back(switchs[i][1]);
            graph[switchs[i][1]].push_back(switchs[i][0]);
            graph[switchs[i][0] + JUMP].push_back(switchs[i][1] + JUMP);
            graph[switchs[i][1] + JUMP].push_back(switchs[i][0] + JUMP);
        }
        else {
            graph[switchs[i][0]].push_back(switchs[i][1] + JUMP);
            graph[switchs[i][1] + JUMP].push_back(switchs[i][0]);
            graph[switchs[i][1]].push_back(switchs[i][0] + JUMP);
            graph[switchs[i][0] + JUMP].push_back(switchs[i][1]);
        }
    }

    for (int i = 1; i <= m; i++)
        if (!dfs_num[i])
            dfs(i);
    for (int i = JUMP+1; i <= JUMP+m; i++)
        if (!dfs_num[i])
            dfs(i);

    for (int i = 1; i <= m; i++)
        if (cp[i] == cp[i+JUMP]) {
            printf("NO\n");
            exit(0);
        }
    printf("YES\n");

    return 0;
}

