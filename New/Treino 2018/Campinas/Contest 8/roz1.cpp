#include <bits/stdc++.h>

using namespace std;

int n, m, k, grid[3030][3030], cnt[100100];

int main() {
    clock_t tStart = clock();

    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &grid[i][j]);

    int var = 0, best = 0;
    long long sum = 0;
    for (int i = 0; i < n - k + 1; i++) {
        memset(cnt, 0, sizeof cnt);
        var = 0;

        for (int j = i; j < i+k; j++)
            for (int l = 0; l < k; l++)
                var += !cnt[grid[j][l]]++;

        best = max(best, var);
        sum += var;

        for (int j = 1; j < m - k + 1; j++) {
            for (int l = i; l < i+k; l++) {
                var -= !--cnt[grid[l][j-1]];
                var += !cnt[grid[l][j+k-1]]++;
            }
            best = max(best, var);
            sum += var;
        }
    }

    printf("%d %lld\n", best, sum);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}
