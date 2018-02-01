#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll n, s;

int main() {
    scanf("%lld %lld", &n, &s);

    ll ini = 1, fim = n;
    while (ini <= fim) {
        ll mid = (ini + fim) / 2;

        ll sum = 0, aux = mid;
        while (aux) {
            sum += aux % 10;
            aux /= 10;
        }

        if (mid - sum < s) ini = mid+1;
        else fim = mid-1;
    }
    printf("%lld\n", n - ini + 1);

    return 0;
}

