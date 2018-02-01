#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define MOD 1000000007
#define pii pair < int, int >

int n, m, k;
string s;
bool app[200200];

void calc(int siz) {
    app[siz] = true;
    if (siz == 1) return;
    calc(siz/2); calc(siz - siz/2);
}

ll dp[5][5200020];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    cin >> s;
    int val = 0;
    for (int i = 0; i < n; i++)
        val += s[i] - 'a';

    calc(n);
    deque < int > lvls;
    for (int i = 1; i <= n; i++)
        if (app[i])
            lvls.push_back(i);

    //DP

    ll ans = 0;
    for (int i = 0; i < 105; i++) {
        ll lft = m*i + k - val;
        if (lft >= n && lft <= 26*n) {
            ans += dp[n][lft];
            ans %= MOD;
        }
    }
    printf("%lld\n", ans);

    return 0;
}
