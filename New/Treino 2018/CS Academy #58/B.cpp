#include <bits/stdc++.h>

using namespace std;

int n;

struct inv {
    int a, b;
} invs[2020];

bool cmp(inv a, inv b) {
    return a.a < b.a;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &invs[i].a, &invs[i].b);

    sort(invs, invs+n, cmp);

    long long ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        long long aux = 0;
        int pos = invs[i].a;
        for (int j = i-1; j >= 0; j--) {
            aux += pos - invs[j].b;
            pos -= invs[j].b - invs[j].a;
        }
        pos = invs[i].b;
        for (int j = i+1; j < n; j++) {
            aux += invs[j].a - pos;
            pos += invs[j].b - invs[j].a;
        }

        ans = min(ans, aux);
    }

    printf("%lld\n", ans);
    return 0;
}
