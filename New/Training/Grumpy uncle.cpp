#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int n, m, paths[1010][1010];
vector < pair < int, int > > graph[1010][1010];
bool visited[1010][1010];

void dfs(int x, int y) {
    visited[x][y] = true;

    for (pair < int, int > p : graph[x][y])
        if (!visited[p.first][p.second])
            dfs(p.first, p.second);
}

int main() {
    while (scanf("%d %d", &n, &m) != EOF) {
        for (int i = 0; i < 1010; i++)
            for (int j = 0; j < 1010; j++) {
                paths[i][j] = 0;
                graph[i][j].clear();
                visited[i][j] = false;
            }

        for (int i = 1; i <= n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &paths[i][j]);

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 0; k < m; k++) {
                    graph[paths[i][k]][paths[j][k]].push_back(make_pair(i, j));
                }

        dfs(1, 1);

        bool possible = true;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (!visited[i][j])
                    possible = false;

        if (possible) printf("S\n");
        else printf("N\n");
    }

    return 0;
}
