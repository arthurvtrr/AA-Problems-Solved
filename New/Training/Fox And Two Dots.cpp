#include <bits/stdc++.h>

using namespace std;

int n, m;
char grid[55][55];
bool visited[55][55], cycle;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void dfs(int x, int y, int px, int py) {
    visited[x][y] = true;

    for (int i = 0; i < 4; i++)
        if (x + dx[i] >= 0 && x + dx[i] < n && y + dy[i] >= 0 && y + dy[i] < m) {
            if (!visited[x+dx[i]][y+dy[i]] && grid[x+dx[i]][y+dy[i]] == grid[x][y])
                dfs(x+dx[i], y+dy[i], x, y);
            else if (visited[x+dx[i]][y+dy[i]] && x+dx[i] != px && y+dy[i] != py && grid[x+dx[i]][y+dy[i]] == grid[x][y])
                cycle = true;
        }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", grid[i]);

    cycle = false;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!visited[i][j])
                dfs(i, j, -1, -1);

    if (cycle) printf("Yes\n");
    else printf("No\n");

    return 0;
}
