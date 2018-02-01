#include <bits/stdc++.h>

using namespace std;

int m, n, s;
char grid[110][110], pos[300];
string moves;
int cx[4] = {-1, 0, 1, 0};
int cy[4] = {0, 1, 0, -1};

int main() {
    pos['N'] = 0; pos['L'] = 1;
    pos['S'] = 2; pos['O'] = 3;

    while (1) {
        scanf("%d %d %d", &n, &m, &s);
        if (n + m + s == 0) break;

        for (int i = 0; i < n; i++)
            scanf("%s", grid[i]);

        cin >> moves;

        int x, y, dir;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (grid[i][j] != '.' && grid[i][j] != '*' && grid[i][j] != '#') {
                    x = i; y = j; dir = pos[grid[i][j]];
                }

        int ans = 0;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i] == 'E') dir = (dir+3) % 4;
            else if (moves[i] == 'D') dir = (dir+1) % 4;
            else {
                int a = x+cx[dir], b = y+cy[dir];
                if (a >= 0 && a < n && b >= 0 && b < m && grid[a][b] != '#') {
                    x = a; y = b;
                    if (grid[a][b] == '*') {
                        ans++;
                        grid[a][b] = '.';
                    }
                }
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

