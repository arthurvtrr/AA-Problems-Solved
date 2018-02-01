#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, m, k;

struct flight {
    int d, f, t;
    ll c;
} f[100100];

bool cmp1(flight a, flight b) {
    return a.d < b.d;
}

bool cmp2(flight a, flight b) {
    return a.d > b.d;
}

ll aux[100100], ini[1001000], fim[1001000];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < m; i++)
        scanf("%d %d %d %lld", &f[i].d, &f[i].f, &f[i].t, &f[i].c);

    sort(f, f+m, cmp1);

    ll quant = 0, cost = 0, pos = 0;
    for (int i = 1; i < 1001000; i++) {
        while (f[pos].d == i && pos < m) {
            if (f[pos].f == 0) {
                pos++;
                continue;
            }

            if (aux[f[pos].f] == 0) {
                aux[f[pos].f] = f[pos].c;
                cost += f[pos].c;
                quant++;
            }
            else if (aux[f[pos].f] > f[pos].c) {
                cost -= aux[f[pos].f];
                cost += f[pos].c;
                aux[f[pos].f] = f[pos].c;
            }
            pos++;
        }

        if (quant < n) ini[i] = -1;
        else ini[i] = cost;
    }

    memset(aux, 0, sizeof aux);

    sort(f, f+m, cmp2);

    quant = 0, cost = 0, pos = 0;
    for (int i = 1000999; i > 0; i--) {
        while (f[pos].d == i && pos < m) {
            if (f[pos].t == 0) {
                pos++;
                continue;
            }

            if (aux[f[pos].t] == 0) {
                aux[f[pos].t] = f[pos].c;
                cost += f[pos].c;
                quant++;
            }
            else if (aux[f[pos].t] > f[pos].c) {
                cost -= aux[f[pos].t];
                cost += f[pos].c;
                aux[f[pos].t] = f[pos].c;
            }
            pos++;
        }

        if (quant < n) fim[i] = -1;
        else fim[i] = cost;
    }

    ll ans = LLONG_MAX;
    for (int i = 2; i < 1001000 - k - 1; i++)
        if (ini[i-1] != -1 && fim[i+k] != -1)
            ans = min(ans, ini[i-1] + fim[i+k]);

    printf("%lld\n", ans == LLONG_MAX? -1 : ans);

    return 0;
}
