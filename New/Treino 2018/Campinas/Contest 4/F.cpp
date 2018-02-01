#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll n, dp[75][75][2][2], dp1[75][75][2][2];
string lim;

ll solve(int ind, int siz, int f, int l) {
    if (dp[ind][siz][f][l] != -1) return dp[ind][siz][f][l];
    if (ind == lim.size()) return siz;

    ll ret = 0;
    if (f || lim[ind] == '1') {
        if (!l) ret += solve(ind+1, siz == 0? (int)lim.size() - ind : siz, f, true);
        ret += solve(ind+1, siz, true, false);
    }
    else ret += solve(ind+1, siz, f, false);

    return dp[ind][siz][f][l] = ret;
}

ll solve1(int ind, int siz, int f, int l) {
    if (dp1[ind][siz][f][l] != -1) return dp1[ind][siz][f][l];
    if (ind == lim.size()) return siz;

    ll ret = 0;
    if (f || lim[ind] == '1') {
        if (!l) ret += solve1(ind+1, siz+1, f, true);
        ret += solve1(ind+1, siz, true, false);
    }
    else ret += solve1(ind+1, siz, f, false);

    return dp1[ind][siz][f][l] = ret;
}

#define ull unsigned long long

int main() {
    freopen("fibonacci.in", "r", stdin);
    freopen("fibonacci.out", "w", stdout);

    scanf("%lld", &n);

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    ull ini = 1, fim = (1LL << 63) - 100;
    while (ini <= fim) {
        ull meio = (ini + fim) / 2;

        memset(dp, -1, sizeof dp);
        lim = "";
        for (int i = 63; i >= 0; i--) {
            if (meio & (1LL << i)) lim += '1';
            else lim += '0';
        }

        ull quant = solve(0, 0, false, false);

        if (quant < n) ini = meio+1;
        else fim = meio-1;
    }

    memset(dp, -1, sizeof dp);
    lim = "";
    for (int i = 63; i >= 0; i--) {
        if ((ini-1) & (1LL << i)) lim += '1';
        else lim += '0';
    }
    ull lft = n - solve(0, 0, false, false);

    memset(dp1, -1, sizeof dp1);
    ull ans = solve1(0, 0, false, false);

    lim = "";
    bool f = false;
    for (int i = 63; i >= 0; i--) {
        if (lft == 0) break;

        if (ini & (1LL << i)) { lim += '1'; f = true; ans++; }
        else lim += '0';

        if (f) lft--;
    }

    printf("%llu\n", ans);

    return 0;
}
