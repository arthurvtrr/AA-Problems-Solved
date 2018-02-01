#include <bits/stdc++.h>

using namespace std;

int n, nums[1001000], val[1001000], bit[2002000];

void update(int pos, int val) {
    while (pos < 2002000) {
        bit[pos] += val;
        pos += pos & -pos;
    }
}

int query(int pos) {
    int ret = 0;
    while (pos) {
        ret += bit[pos];
        pos -= pos & -pos;
    }
    return ret;
}

#define ll long long

int main() {
    scanf("%d", &n);

    ll ans = 0, best = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        val[i] = nums[i] - i - 1;
        ans += abs(val[i]);
        update(val[i]+n, 1);
    }

    int last = n-1;
    ll x = ans;

    for (int i = 1; i < n; i++) {
        update(val[last] + n, -1);
        val[last] -= i - 1;

        x += val[last] + n - 1 - abs(val[last]);
        x -= query(2001999) - query(i+n-1);
        x += query(i+n-1);
        update(val[last] + n - 1 + i + n, 1);
        last--;

        if (x < ans) {
            ans = x;
            best = i;
        }
    }
    printf("%lld %lld\n", ans, best);

    return 0;
}
