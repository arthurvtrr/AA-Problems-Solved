#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define INF 100000000000000

int n, m;
ll nums[550][550];
bitset < 550 > aux, fim;

ll solve(int ind, bitset < 550 > mask) {
    if (ind == m) {
        if (mask == fim) return 0;
        return INF;
    }

    ll ret = solve(ind+1, mask);

    aux.reset();
    for (int i = 0; i < n; i++)
        if (nums[ind][i] == 1)
            aux[i] = 1;
    aux |= mask;

    if (aux != mask) ret = min(ret, solve(ind+1, aux) + nums[ind][n]);

    return ret;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n+1; j++)
            scanf("%lld", &nums[i][j]);

    for (int i = 0; i < n; i++) fim[i] = 1;

    printf("%lld\n", solve(0, aux));

    return 0;
}
