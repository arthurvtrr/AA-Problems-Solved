#include <stdio.h>
#include <algorithm>

using namespace std;

#define ll long long

ll t, w, b, prob;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%I64d %I64d %I64d", &t, &w, &b);

    prob = t / max(w,b);

    ll div = gcd(prob, t);
    ll x = prob / div, y = t / div;

    printf("%I64d/%I64d\n", x, y);
    return 0;
}
