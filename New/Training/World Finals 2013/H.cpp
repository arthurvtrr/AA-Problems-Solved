#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000

int n, nums[550], dp1[550], dp2[550][550], mini[550][550], pos[505][505][505];

int quant(int l, int r) {
    if (dp2[l][r] != -1) return dp2[l][r];
    if (l == r) return 0;

    int ret = INF;

    for (int i = l; i < r; i++)
        ret = min(ret, r - l + 1 - pos[l][r][max(mini[l][i], mini[i+1][r])] + quant(l, i) + quant(i+1, r));

    return dp2[l][r] = ret;
}

int solve(int ind) {
    if (dp1[ind] != -1) return dp1[ind];
    if (ind == n) return 0;

    int ret = INF;
    set < int > found;
    for (int i = ind; i < n; i++) {
        found.insert(nums[i]);
        if (found.size() == i - ind + 1 && *found.rbegin() == i - ind + 1)
            ret = min(ret, quant(ind, i) + solve(i+1));
    }

    return dp1[ind] = ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    memset(dp1, -1, sizeof dp1);
    memset(dp2, -1, sizeof dp2);

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            int x = nums[i];
            for (int k = i; k <= j; k++)
                x = min(x, nums[k]);
            mini[i][j] = x;

            set < int > aux;
            for (int k = i; k <= j; k++)
                aux.insert(nums[k]);
            int cnt = 0;
            for (auto v : aux)
                pos[i][j][v] = cnt++;
        }

    int ans = solve(0);
    if (ans == INF) printf("impossible\n");
    else printf("%d\n", ans);

    return 0;
}

