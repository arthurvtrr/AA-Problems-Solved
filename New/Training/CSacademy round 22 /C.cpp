#include <bits/stdc++.h>

using namespace std;

int n, m, grid[1010][1010], comp[1010][1010], siz[1001000], sizc;
bool visited[1010][1010];

int cx[4] = {-1, 1, 0, 0};
int cy[4] = {0, 0, -1, 1};

void dfs(int x, int y, int cmp) {
    visited[x][y] = true;
    comp[x][y] = cmp;
    sizc++;

    for (int i = 0; i < 4; i++)
        if (!visited[x+cx[i]][y+cy[i]] && grid[x+cx[i]][y+cy[i]] == 1)
            dfs(x+cx[i], y+cy[i], cmp);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &grid[i][j]);

    int cmp = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (grid[i][j] == 1 && !visited[i][j]) {
                sizc = 0;
                dfs(i, j, cmp);
                siz[cmp++] = sizc;
            }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (grid[i][j] == 0) {
                int aux = 1;
                set < int > comps;
                for (int k = 0; k < 4; k++)
                    comps.insert(comp[i+cx[k]][j+cy[k]]);
                for (auto v : comps)
                    aux += siz[v];

                ans = max(ans, aux);
            }

    printf("%d\n", ans);

    return 0;
}

