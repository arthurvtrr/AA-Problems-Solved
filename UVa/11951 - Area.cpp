#include <stdio.h>
#include <algorithm>

using namespace std;

int t, n, m, k, nums[110][110], col_s[110][110];
long long sol, area;

void solve(int x, int y) {
    for (int i = x; i <= n; i++) {
        long long aux = 0;
        for (int j = y; j <= m; j++) {
            aux += col_s[i][j] - col_s[x-1][j];

            if ((i-x+1) * (j-y+1) > area && aux <= k) {
                sol = aux;
                area = (i-x+1) * (j-y+1);
            }
            else if ((i-x+1) * (j-y+1) == area && aux < sol) {
                sol = aux;
                area = (i-x+1) * (j-y+1);
            }
        }
    }
}

int main() {
    scanf("%d", &t);

    for (int tc = 1; tc <= t; tc++) {
        scanf("%d %d %d", &n, &m, &k);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                scanf("%d", &nums[i][j]);

        sol = 0, area = 0;

        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++) {
                col_s[j][i] = nums[j][i];
                col_s[j][i] += col_s[j-1][i];
            }

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                solve(i, j);

        printf("Case #%d: %lld %lld\n", tc, area, sol);
    }
    return 0;
}

