#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t;
ll n, val[2002000], acum[2002000], ans[1001000];

int main() {
    for (int i = 1; i < 2002000; i++) {
        int sum[2] = {0, 0}, aux = i;
        while (aux) {
            sum[(aux % 10) & 1] += aux % 10;
            aux /= 10;
        }
        val[i] = abs(sum[0] - sum[1]);
    }
    for (int i = 1; i < 2002000; i++) {
        acum[i] = 2*val[i];
        acum[i] += acum[i-1];
    }
    ans[1] = val[2];
    for (int i = 2; i < 1001000; i++) {
        ans[i] = ans[i-1];
        ans[i] += acum[2*i-1] - acum[i];
        ans[i] += val[2*i];
    }

    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        printf("%lld\n", ans[n]);
    }

    return 0;
}
