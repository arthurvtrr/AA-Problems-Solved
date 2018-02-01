#include <bits/stdc++.h>

using namespace std;

int n, k, nums[100100];
int best[55][55], aux[55][55];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    memset(best, -1, sizeof best);
    best[0][nums[0]] = 1;

    for (int i = 1; i < n; i++) {
        for (int a = 0; a <= k; a++)
            for (int b = 0; b < 55; b++)
                aux[a][b] = best[a][b];

        for (int a = 0; a <= k; a++)
            for (int b = 0; b < 55; b++)
                if (best[a][b] != -1)
                    aux[a + abs(b - nums[i])][nums[i]] = max(aux[a + abs(b - nums[i])][nums[i]], best[a][b] + 1);

        for (int a = 0; a <= k; a++)
            for (int b = 0; b < 55; b++)
                best[a][b] = aux[a][b];
    }

    int ans = 0;
    for (int i = 0; i <= k; i++)
        for (int j = 0; j < 55; j++)
            ans = max(ans, best[i][j]);
    printf("%d\n", ans);

    return 0;
}
