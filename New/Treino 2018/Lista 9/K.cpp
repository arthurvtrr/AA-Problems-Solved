#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, use[4] = {2, 3, 5, 7};
set < ll > aux;
ll p10[19];

bool prime(ll x) {
    for (int i = 2; i <= sqrt(x); i++)
        if (x % i == 0)
            return false;
    return true;
}

int main() {
    p10[0] = 1;
    for (int i = 1; i < 19; i++)
        p10[i] = p10[i-1] * 10;

    for (int i = 0; i < 4; i++)
        aux.insert(use[i]);

    scanf("%d", &n);
    int ind = 1;
    while (n > 1 && !aux.empty()) {
        ll x = *aux.begin();
        aux.erase(aux.begin());
        for (int i = 0; i < 4; i++) {
            ll y = x*10 + use[i];
            bool val = true;
            for (int j = 1; j < 19; j++) {
                ll z = y % p10[j];
                if (!prime(z)) val = false;
            }
            if (val) aux.insert(y);
        }
        n--;
    }
    if (aux.empty()) printf("-1\n");
    else printf("%lld\n", *aux.begin());
    return 0;
}
