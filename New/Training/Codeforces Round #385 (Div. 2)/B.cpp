#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, m;
char grid[505][505];

int main() {
    scanf("%d %d", &n, &m);

    int siz = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf(" %c", &grid[i][j]);
            if (grid[i][j] == 'X')
                siz++;
        }

    int firstx = 1000, firsty = 1000, lastx = 0, lasty = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (grid[i][j] == 'X') {
                firstx = min(firstx, i);
                firsty = min(firsty, j);
                lastx = max(lastx, i);
                lasty = max(lasty, j);
            }

    if ((lastx - firstx + 1) * (lasty - firsty + 1) == siz) printf("YES\n");
    else printf("NO\n");

    return 0;
}
