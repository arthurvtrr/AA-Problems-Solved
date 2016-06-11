#include <stdio.h>
#include <algorithm>

using namespace std;

int t, n, a, nums[200][200], col_s[200][200];
int sol;

void solve(int x, int y) {
    for (int i = x; i < min(x+n, n*2+1); i++) {
        int aux = 0;
        for (int j = y; j < min(y+n, n*2+1); j++) {
            aux += col_s[i][j] - col_s[x-1][j];
            sol = max(sol, aux);
        }
    }
}

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                scanf("%d", &a);
                nums[i][j] = a;
                nums[i+n][j] = a;
                nums[i][j+n] = a;
                nums[i+n][j+n] = a;
            }

        sol = nums[1][1];

        for (int i = 1; i <= n*2; i++)
            for (int j = 1; j <= n*2; j++) {
                col_s[j][i] = nums[j][i];
                col_s[j][i] += col_s[j-1][i];
            }

        for (int i = 1; i <= n*2; i++)
            for (int j = 1; j <= n*2; j++)
                solve(i, j);

        printf("%d\n", sol);
    }
    return 0;
}
