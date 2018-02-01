#include <bits/stdc++.h>

using namespace std;

int t, n, m;
char grid[1010][1010];

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%s", grid[i]);

        bool valid = true;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'B' && i < n-1 && grid[i+1][j] != 'B')
                    valid = false;
                if (grid[i][j] == 'W' && (j == 0 || j == m-1 || grid[i][j-1] == 'A' || grid[i][j+1] == 'A' || grid[i+1][j] == 'A'))
                    valid = false;
            }

        if (valid) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}
