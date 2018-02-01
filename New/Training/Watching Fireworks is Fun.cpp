#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define INF 10000000000000000LL
#define N 150500
#define pll pair < ll, ll >

int n, m;
ll dp[N][2], d;

struct fire {
    int pos;
    ll b, t;
} fires[303];

int main() {
    scanf("%d %d %lld", &n, &m, &d);
    for (int i = 1; i <= m; i++)
        scanf("%d %lld %lld", &fires[i].pos, &fires[i].b, &fires[i].t);

    for (int i = 1; i < N; i++)
        dp[i][0] = dp[i][1] = -INF;

    for (int i = 1; i <= n; i++)
        dp[i][m & 1] = fires[m].b - abs(fires[m].pos - i);

    deque < pll > aux;
    for (int i = m-1; i > 0; i--) {
        aux.clear();
        ll dist = d * (fires[i+1].t - fires[i].t);

        int pos = 1;
        for (int j = 1; j <= n; j++) {
            while (pos <= n && pos - j <= dist) {
                while (!aux.empty() && aux.back().first <= dp[pos][(i+1) & 1]) aux.pop_back();
                aux.push_back(pll(dp[pos][(i+1) & 1], pos));
                pos++;
            }
            pos--;
            while (!aux.empty() && j - aux.front().second > dist) aux.pop_front();

            dp[j][i & 1] = aux.front().first + fires[i].b - abs(fires[i].pos - j);
        }
    }

    ll ans = -INF;
    for (int i = 1; i <= n; i++)
        ans = max(ans, dp[i][1]);
    printf("%lld\n", ans);

    return 0;
}
