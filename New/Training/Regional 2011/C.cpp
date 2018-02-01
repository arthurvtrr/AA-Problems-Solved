#include <bits/stdc++.h>

using namespace std;

int n, f, nums[50], aux, atual;
int dp[41][80080];

int solve(int ind, int total) {
    if (dp[ind][total] != -1) return dp[ind][total];
    if (ind == atual) return solve(ind+1, total);
    if (ind == n) return total - 40000 == aux;

    int ret = 0;
    ret += solve(ind+1, total - nums[ind]);
    ret += solve(ind+1, total + nums[ind]);

    return dp[ind][total] = ret > 0;
}

int main() {
    while (1) {
        scanf("%d %d", &n, &f);
        if (n + f == 0) break;

        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
            sum += nums[i];
        }

        string ans = "";
        for (int i = 0; i < n; i++) {
            char c = '*';
            atual = i;

            aux = f + nums[i];

            for (int a = 0; a <= n; a++)
                for (int b = 40000 - sum; b <= 40000 + sum; b++)
                    dp[a][b] = -1;

            if (solve(0, 40000) > 0) c = '-';

            aux = f - nums[i];

            for (int a = 0; a <= n; a++)
                for (int b = 40000 - sum; b <= 40000 + sum; b++)
                    dp[a][b] = -1;

            if (solve(0, 40000) > 0) {
                if (c == '*') c = '+';
                else c = '?';
            }

            if (c == '*') { ans = "*"; break; }
            else ans += c;
        }
        cout << ans << endl;
    }

    return 0;
}

