#include <bits/stdc++.h>

using namespace std;

#define ll long long

string aux;
ll s, dp[30][30];
bool carry[30];

ll solve(int dig, int q) {
    if (dp[dig][q] != -1) return dp[dig][q];
    if (dig == aux.size()) return q == 0;

    ll ret = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++) {
            if (carry[dig] && i + j + q > 9 && (i + j + q) % 10 == aux[dig] - '0') ret += solve(dig+1, (i + j + q) / 10);
            else if (!carry[dig] && i + j + q <= 9 && i + j + q == aux[dig] - '0') ret += solve(dig+1, 0);
        }

    return dp[dig][q] = ret;
}

int main() {
    cin >> aux;
    s = 0;
    for (int i = 0; i < aux.size(); i++) {
        s *= 10;
        s += (aux[i] - '0');
    }
    reverse(aux.begin(), aux.end());

    for (int i = 0; i < (int)aux.size() - 1; i++)
        scanf("%d", &carry[i]);

    memset(dp, -1, sizeof dp);
    printf("%lld\n", solve(0, 0));

    return 0;
}


