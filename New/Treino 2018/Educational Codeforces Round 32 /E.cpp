#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll n, m, nums[40];

int main() {
    scanf("%lld %lld", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);

    if (n == 1) {
        printf("%lld\n", nums[0] % m);
        return 0;
    }

    vector < ll > a, b, c, d;
    for (int i = 0; i < n/2; i++)
        a.push_back(nums[i]);
    for (int i = n/2; i < n; i++)
        b.push_back(nums[i]);

    for (int i = 0; i < 1 << a.size(); i++) {
        ll aux = 0;
        for (int j = 0; j < a.size(); j++)
            if (i & (1 << j))
                aux += a[j];
        c.push_back(aux % m);
    }

    for (int i = 0; i < 1 << b.size(); i++) {
        ll aux = 0;
        for (int j = 0; j < b.size(); j++)
            if (i & (1 << j))
                aux += b[j];
        d.push_back(aux % m);
    }

    sort(c.begin(), c.end());
    sort(d.begin(), d.end());

    ll ans = 0;
    for (int i = 0; i < c.size(); i++)
        ans = max(ans, (c[i] + d.back()) % m);

    int pos = (int)d.size() - 1;
    for (int i = 0; i < c.size(); i++) {
        while (pos >= 0 && c[i] + d[pos] >= m) pos--;
        if (pos == -1) break;
        ans = max(ans, c[i] + d[pos]);
    }
    printf("%lld\n", ans);

    return 0;
}
