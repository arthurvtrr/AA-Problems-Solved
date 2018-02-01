#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int t, r, c;
char grid[30][30];

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 30; j++)
                grid[i][j] = '.';

        scanf("%d %d", &r, &c);
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                cin >> grid[i][j];

        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                if (grid[i][j] != '?') {
                    int min_x = i, max_x = i, min_y = j, max_y = j;

                    for (int a = min_y-1; a >= 0; a--)
                        if (grid[i][a] != '?') {
                            min_y = a + 1;
                            break;
                        }

                    while (1) {
                        bool up = true;
                        for (int a = min_y; a <= max_y; a++)
                            if (grid[min_x-1][a] != '?')
                                up = false;
                        if (!up) break;
                        else min_x--;
                    }

                    while (1) {
                        bool possible = true;
                        for (int a = min_x; a <= max_x; a++)
                            if (grid[a][max_y+1] != '?')
                                possible = false;

                        if (!possible) break;
                        else max_y++;
                    }

                    for (int a = min_x; a <= max_x; a++)
                        for (int b = min_y; b <= max_y; b++)
                            grid[a][b] = grid[i][j];
                }

        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                if (grid[i][j] == '?')
                    grid[i][j] = grid[i-1][j];

        printf("Case #%d:\n", tc+1);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++)
                cout << grid[i][j];
            printf("\n");
        }
    }

    return 0;
}
