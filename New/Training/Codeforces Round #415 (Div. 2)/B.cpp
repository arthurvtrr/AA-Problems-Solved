#include <bits/stdc++.h>

using namespace std;

int n, f;

struct p {
    long long k, l;
} ps[100100];

bool cmp(p a, p b) {
    return min(a.k * 2, a.l) - min(a.k, a.l) > min(b.k * 2, b.l) - min(b.k, b.l);
}

int main() {
    scanf("%d %d", &n, &f);
    for (int i = 0; i < n; i++)
        scanf("%lld %lld", &ps[i].k, &ps[i].l);

    sort(ps, ps+n, cmp);

    long long sold = 0;
    for (int i = 0; i < n; i++) {
        if (i < f) sold += min(2 * ps[i].k, ps[i].l);
        else sold += min(ps[i].k, ps[i].l);
    }
    printf("%lld\n", sold);

    return 0;
}
