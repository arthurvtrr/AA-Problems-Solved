#include <bits/stdc++.h>

using namespace std;

#define ull unsigned long long

ull x, y, l, r;

int main() {
    scanf("%llu %llu %llu %llu", &x, &y, &l, &r);

    set < ull > unlucky;
    ull a = 1, b = 1;
    while (b <= r) {
        ull aux = a;
        while (aux <= r) {
            if (aux + b >= l && aux + b <= r)
                unlucky.insert(aux + b);
            if (aux > r / x) break;
            aux *= x;
        }
        if (b > r / y) break;
        b *= y;
    }

    unlucky.insert(r+1);

    ull ans = 0, last = l-1;
    for (auto v : unlucky) {
        ans = max(ans, v - last - 1);
        last = v;
    }
    printf("%llu\n", ans);

    return 0;
}
