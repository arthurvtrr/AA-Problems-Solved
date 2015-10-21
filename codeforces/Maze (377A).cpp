#include <stdio.h>
#include <stdlib.h>

int n, m, k, remain;
bool test[550][550];
char maze[550][550];

using namespace std;

void dfs(int l, int c) {
    test[l][c] = true;
    remain -= 1;
    if (remain == 0)
        return;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (abs(i) + abs(j) == 1) {
                    int x = l + i;
                    int y = c + j;
                    if (x >= 0 && x < n && y >= 0 && y < m && !test[x][y]) {
                        dfs(x,y);
                        if (remain == 0)
                            return;
                    }
                }
        }
    }
}

int main()
{
    int l, c;

    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        scanf("%s", &maze[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == '#')
                test[i][j] = true;
            else {
                remain++;
                l = i;
                c = j;
            }
        }
    }

    remain -= k;
    dfs(l,c);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (!test[i][j])
                printf("X");
            else
                printf("%c", maze[i][j]);
        }
        printf("\n");
    }

    return 0;
}