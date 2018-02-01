#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

char grid[5][5];

bool valid(int a, int b, int c, int d) {
    if (a < 0 || a >= 4) return false;
    if (b < 0 || b >= 4) return false;
    if (c < 0 || c >= 4) return false;
    if (d < 0 || d >= 4) return false;

    if (grid[a][b] == 'x' && grid[c][d] == '.') return true;
    if (grid[a][b] == '.' && grid[c][d] == 'x') return true;
    return false;
}

int main() {
    for (int i = 0; i < 4; i++)
        scanf("%s", grid[i]);

    bool possible = false;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 'x') {
                if (valid(i-1, j, i-2, j) || valid(i+1, j, i+2, j) || valid(i, j-1, i, j-2) || valid(i, j+1, i, j+2)) possible = true;
                if (valid(i-1, j-1, i-2, j-2) || valid(i+1, j-1, i+2, j-2) || valid(i+1, j+1, i+2, j+2) || valid(i-1, j+1, i-2, j+2)) possible = true;
            }

    if (possible) printf("YES\n");
    else printf("NO\n");
    return 0;
}
