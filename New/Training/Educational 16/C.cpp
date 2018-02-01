#include <bits/stdc++.h>

using namespace std;

int n, grid[50][50];

int main() {
    scanf("%d", &n);

    int left = (n*n + 1) / 2, next = 1;

    for (int i = 0; i < n; i++) {
        grid[i][n/2] = next;
        next += 2;
        left--;
    }
    for (int i = 0; i < n; i++)
        if (grid[n/2][i] == 0) {
            grid[n/2][i] = next;
            next += 2;
            left--;
        }

    for (int i = 0; i < n/2; i++)
        for (int j = 0; j < n/2; j++) {
            if (left == 0) break;

            grid[i][j] = next;
            next += 2;
            grid[n-i-1][j] = next;
            next += 2;
            grid[i][n-j-1] = next;
            next += 2;
            grid[n-i-1][n-j-1] = next;
            next += 2;

            left -= 4;
        }

    int even = 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j) printf(" ");
            printf("%d", grid[i][j] == 0? even : grid[i][j]);
            if (grid[i][j] == 0) even += 2;
        }
        printf("\n");
    }

    return 0;
}

