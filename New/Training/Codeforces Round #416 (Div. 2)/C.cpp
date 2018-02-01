#include <bits/stdc++.h>

using namespace std;

int n, nums[5050], quant[5050], dp[5050], aux[5050][5050];

int solve(int ind) {
    if (dp[ind] != -1) return dp[ind];
    if (ind == n) return 0;

    int ret = 0, val = 0, diff = 0, corr = 0;
    ret = solve(ind+1);

    for (int i = ind; i < n; i++) {
        if (aux[ind][nums[i]] == 0) { diff++; val ^= nums[i]; }
        aux[ind][nums[i]]++;
        if (aux[ind][nums[i]] == quant[nums[i]]) corr++;

        if (diff == corr) ret = max(ret, val + solve(i+1));
    }

    return dp[ind] = ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        quant[nums[i]]++;
    }

    for (int i = 0; i < 5050; i++)
        dp[i] = -1;

    printf("%d\n", solve(0));

    return 0;
}

