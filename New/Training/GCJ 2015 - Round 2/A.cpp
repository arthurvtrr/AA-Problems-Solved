#include <bits/stdc++.h>

using namespace std;

int t, r, c;
char grid[110][110];
bool loop[110][110], visited[110][110];

#define pii pair < int, int >

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d %d", &r, &c);

        for (int i = 0; i < r; i++)
            scanf("%s", grid[i]);

        memset(loop, 0, sizeof loop);
        memset(visited, 0, sizeof visited);

        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (grid[i][j] == '.')
                    loop[i][j] = true;

        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (!visited[i][j] && grid[i][j] != '.') {
                    vector < pii > aux;

                    int ax = i, ay = j, cx = 0, cy = 0;
                    while (ax >= 0 && ax < r && ay >= 0 && ay < c && !visited[ax][ay]) {
                        if (grid[ax][ay] != '.') {
                            aux.push_back(pii(ax, ay));
                            visited[ax][ay] = true;
                        }

                        if (grid[ax][ay] == '^') { cx = -1; cy = 0; }
                        else if (grid[ax][ay] == 'v') { cx = 1; cy = 0; }
                        else if (grid[ax][ay] == '<') { cx = 0; cy = -1; }
                        else if (grid[ax][ay] == '>') { cx = 0; cy = 1; }

                        ax += cx; ay += cy;
                    }

                    if (ax >= 0 && ax < r && ay >= 0 && ay < c && visited[ax][ay]) {
                        for (pii v : aux)
                            loop[v.first][v.second] = true;
                    }
                    else {
                        for (int v = 0; v < aux.size() - 1; v++)
                            loop[aux[v].first][aux[v].second] = true;
                    }
                }

        bool valid = true;
        int cnt = 0;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++) {
                if (loop[i][j]) continue;
                cnt++;

                bool found = false;
                for (int k = i-1; k >= 0; k--)
                    if (grid[k][j] != '.')
                        found = true;
                for (int k = i+1; k < r; k++)
                    if (grid[k][j] != '.')
                        found = true;
                for (int k = j-1; k >= 0; k--)
                    if (grid[i][k] != '.')
                        found = true;
                for (int k = j+1; k < c; k++)
                    if (grid[i][k] != '.')
                        found = true;

                if (!found)
                    valid = false;
            }

        if (!valid) printf("Case #%d: IMPOSSIBLE\n", tc);
        else printf("Case #%d: %d\n", tc, cnt);
    }
    return 0;
}
