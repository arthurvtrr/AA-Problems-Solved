#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, m, k, x, y;
char grid[1010][1010];
set < pii > seen;
vector < pii > vis;
bool visited[1010][1010];
int ans[1010][1010];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y) {
    visited[x][y] = true;
    vis.push_back(pii(x, y));
    for (int i = 0; i < 4; i++)
        if (x+dx[i] >= 0 && x+dx[i] < n && y+dy[i] >= 0 && y+dy[i] < m) {
            if (!visited[x+dx[i]][y+dy[i]]) {
                if (grid[x+dx[i]][y+dy[i]] == '*') seen.insert(pii(x*1000 + y, (x+dx[i])*1000 + y+dy[i]));
                else dfs(x+dx[i], y+dy[i]);
            }
        }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++)
        scanf("%s", grid[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!visited[i][j] && grid[i][j] == '.') {
                dfs(i, j);
                for (pii v : vis)
                    ans[v.first][v.second] = seen.size();
                vis.clear();
                seen.clear();
            }

    for (int i = 0; i < k; i++) {
        scanf("%d %d", &x, &y);
        printf("%d\n", ans[x-1][y-1]);
    }

    return 0;
}

