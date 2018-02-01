#include <bits/stdc++.h>

using namespace std;

int n, grid[55][55];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &grid[i][j]);

    bool valid = true;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) continue;
            bool found = false;

            for (int k = 0; k < n; k++)
                for (int l = 0; l < n; l++)
                    if (grid[i][k] + grid[l][j] == grid[i][j])
                        found = true;

            if (!found) valid = false;
        }

    if (valid) printf("Yes\n");
    else printf("No\n");

    return 0;
}
