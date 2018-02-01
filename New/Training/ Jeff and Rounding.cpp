#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int n, x, nums[4040];
int dp[4040][2020];

int solve(int ind, int quant) {
    if (quant > n) return INF;
    if (ind == 2*n) return quant == n? 0 : INF;
    if (dp[ind][quant] != -1) return dp[ind][quant];

    int a = solve(ind+1, quant+1) - nums[ind];
    int b = solve(ind+1, quant) + ((1000-nums[ind]) % 1000);

    if (abs(a) < abs(b)) return dp[ind][quant] = a;
    return dp[ind][quant] = b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 2*n; i++)
        scanf("%d.%d", &x, &nums[i]);

    for (int i = 0; i < 4040; i++)
        for (int j = 0; j < 2020; j++)
            dp[i][j] = -1;

    printf("%.3f\n", abs(solve(0, 0))*1.0/1000);

    return 0;
}
