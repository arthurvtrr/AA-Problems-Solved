#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n;
ll w, h, nums[100100];

int main() {
    scanf("%d %lld %lld", &n, &w, &h);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);

    ll quant = 0, pos = 0;
    for (int i = 0; i < n; i++) {
        if (pos + nums[i] > w) {
            quant += w - pos;
            pos = 0;
        }
        quant += nums[i];
        pos += nums[i];

        if (pos + 1 >= w) {
            quant += w - pos;
            pos = 0;
        }
        else { pos++; quant++; }
    }

    ll ini = 2, fim = w*h;
    while (ini <= fim) {
        ll meio = (ini + fim) / 2;
        if (w*h - nums[0] >= quant * (meio-1) - 1) ini = meio+1;
        else fim = meio-1;
    }
    printf("%lld\n", fim);

    return 0;
}
