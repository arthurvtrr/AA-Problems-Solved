#include <bits/stdc++.h>

using namespace std;

#define ll unsigned long long

ll n, quant[20000000];

int main() {
    scanf("%llu", &n);
    ll ini = 4, fim = 4*n;
    while (ini <= fim) {
        ll meio = (ini + fim) / 2;
        ll sum = 0, aux = sqrt(3*n);
        for (ll i = aux; i > 1; i--) {
            quant[i] = meio / (i*i);
            for (ll j = 2; j <= aux; j++) {
                if (i*j > aux) break;
                quant[i] -= quant[i*j];
            }
            sum += quant[i];
        }

        if (sum >= n) fim = meio-1;
        else ini = meio+1;
    }
    printf("%llu\n", ini);

    return 0;
}
