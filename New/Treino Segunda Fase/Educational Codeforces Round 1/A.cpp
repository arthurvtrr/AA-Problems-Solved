#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t;
ll n;

int main() {
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%lld", &n);
        ll sum = (n+1)*n / 2;
        for (ll j = 1; j <= n; j *= 2)
            sum -= 2*j;
        printf("%lld\n", sum);
    }
    return 0;
}
