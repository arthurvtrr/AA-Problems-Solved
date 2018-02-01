#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, m, k, a[2020], b[2020];
unordered_map < int, int > cnt[2];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; i++)
        scanf("%d", &b[i]);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int siz = 0, val = 0;
        for (int j = 0; j < m; j++) {
            while (val < k && j+siz < m && i+siz < n) {
                val += cnt[0][b[j+siz]];
                cnt[1][b[j+siz]]++;
                val += cnt[1][a[i+siz]];
                cnt[0][a[i+siz]]++;
                siz++;
            }
            if (val >= k) ans += min(n - i - siz + 1, m - j - siz + 1);
            val -= cnt[0][b[j]];
            cnt[1][b[j]]--;
            val -= cnt[1][a[i+siz-1]];
            cnt[0][a[i+siz-1]]--;
            siz--;
        }
    }
    printf("%lld\n", ans);

    return 0;
}
