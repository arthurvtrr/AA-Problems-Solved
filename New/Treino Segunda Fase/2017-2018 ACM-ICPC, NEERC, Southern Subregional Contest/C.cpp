#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll f, t, t0;
ll a1, t1, p1;
ll a2, t2, p2;

int main() {
    scanf("%lld %lld %lld", &f, &t, &t0);
    scanf("%lld %lld %lld", &a1, &t1, &p1);
    scanf("%lld %lld %lld", &a2, &t2, &p2);

    ll ans = LLONG_MAX;

    ll y = 0;
    for (ll x = t / a1 / t1 + 1; x >= 0; x--) {
        while (t - a1*t1*x - a2*t2*y >= 0 && a1*x + a2*y + (t - a1*t1*x - a2*t2*y) / t0 < f) y++;
        if (t - a1*t1*x - a2*t2*y >= 0) ans = min(ans, x*p1 + y*p2);
        else if (y > 0) {
            if (a1*x + a2*(y-1) + (t - a1*t1*x - a2*t2*(y-1)) / t2 >= f) ans = min(ans, x*p1 + y*p2);
        }
    }

    swap(a1, a2); swap(t1, t2); swap(p1, p2);

    y = 0;
    for (ll x = t / a1 / t1 + 1; x >= 0; x--) {
        while (t - a1*t1*x - a2*t2*y >= 0 && a1*x + a2*y + (t - a1*t1*x - a2*t2*y) / t0 < f) y++;
        if (t - a1*t1*x - a2*t2*y >= 0) ans = min(ans, x*p1 + y*p2);
        else if (y > 0) {
            if (a1*x + a2*(y-1) + (t - a1*t1*x - a2*t2*(y-1)) / t2 >= f) ans = min(ans, x*p1 + y*p2);
        }
    }

    if (ans == LLONG_MAX) printf("-1\n");
    else printf("%lld\n", ans);

    return 0;
}
