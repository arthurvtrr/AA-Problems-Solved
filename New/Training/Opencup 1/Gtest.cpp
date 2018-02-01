#include <bits/stdc++.h>

using namespace std;

int n;
char grid[150][150];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%s", &grid[i]);

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            for (int k = 0; k < n; k++)
                for (int l = k+1; l < n; l++)
                    if (grid[i][k] == grid[i][l] && grid[i][l] == grid[j][k] && grid[j][k] == grid[j][l] && grid[j][l] == 'O') {
                        printf("%d %d %d %d\n", i, j, k, l);
                    }

    return 0;
}
