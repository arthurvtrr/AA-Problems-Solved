#include <bits/stdc++.h>

using namespace std;

int n, k1, k2, x;
vector < int > s[2];

int dp[7005][2];

int solve(int id, int p) {
    if (dp[id][p] != -1)
        return dp[id][p];

    for (int i = 0; i < s[p].size(); i++)
        if ((id + s[p][i]) % n == 0)
            return dp[id][p] = 1;

    dp[id][p] = 2;

    for (int i = 0; i < s[p].size(); i++)
        if (dp[(id + s[p][i]) % n][1-p] == -1)
            solve((id + s[p][i]) % n, 1 - p);

    for (int i = 0; i < s[p].size(); i++)
        if (dp[(id + s[p][i]) % n][1-p] == 0)
            return dp[id][p] = 1;

    for (int i = 0; i < s[p].size(); i++)
        if (dp[(id + s[p][i]) % n][1-p] == 2)
            return dp[id][p] = 2;

    return dp[id][p] = 0;
}

int main() {
    scanf("%d", &n);
    scanf("%d", &k1);

    for (int i = 0; i < k1; i++) {
        scanf("%d", &x);
        s[0].push_back(x);
    }
    scanf("%d", &k2);
    for (int i = 0; i < k2; i++) {
        scanf("%d", &x);
        s[1].push_back(x);
    }

    for (int i = 1; i < n; i++) {
        if (i > 1) printf(" ");

        for (int j = 0; j < 7005; j++)
            dp[j][0] = dp[j][1] = -1;

        int aux = solve(i, 0);
        if (aux == 0) printf("Lose");
        else if (aux == 1) printf("Win");
        else printf("Loop");
    }
    printf("\n");

    for (int i = 1; i < n; i++) {
        if (i > 1) printf(" ");

        for (int j = 0; j < 7005; j++)
            dp[j][0] = dp[j][1] = -1;

        int aux = solve(i, 1);
        if (aux == 0) printf("Lose");
        else if (aux == 1) printf("Win");
        else printf("Loop");
    }
    printf("\n");

    return 0;
}
