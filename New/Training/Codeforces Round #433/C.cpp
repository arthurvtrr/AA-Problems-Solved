#include <bits/stdc++.h>

using namespace std;

int n, k, ans[300300];
bool livre[600600];

struct flight {
    int pos;
    long long cost;
} f[300300];

bool cmp(flight a, flight b) {
    if (a.cost == b.cost)
        return a.pos > b.pos;
    return a.cost < b.cost;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &f[i].cost);
        f[i].pos = i;
    }

    sort(f+1, f+n+1, cmp);

    for (int i = n+1; i <= n+k; i++)
        livre[i] = true;

    int atual = 1;
    long long cost = 0;

    for (int i = n+k; i > k; i--) {
        if (!livre[i]) continue;
        while (f[atual].pos >= i) atual++;

        ans[f[atual].pos] = i;
        livre[f[atual].pos] = true;
        cost += f[atual].cost * (i - f[atual].pos);
        atual++;
    }

    printf("%lld\n", cost);
    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        printf("%d", ans[i] == 0? i : ans[i]);
    }
    printf("\n");

    return 0;
}
