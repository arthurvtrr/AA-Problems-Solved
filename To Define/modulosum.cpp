#include <stdio.h>

using namespace std;

bool dp[1100][1100];

int main() {
    int n, m, nums[1100000];
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    if (n > m) printf("YES\n");
    else {
        for (int i = 0; i < m; i++)
            if (nums[0] % m == i) dp[0][i] = true;

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (nums[i] % m == j) dp[i][j] = true;
                else if (dp[i-1][j]) dp[i][j] = true;
                else if (dp[i-1][(j-(nums[i] % m) + m) % m]) dp[i][j] = true;
            }
        }

        if (dp[n-1][0]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
