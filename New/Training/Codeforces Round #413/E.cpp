#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define pll pair < ll, int >

int n, m, k, a, b, x;
bool masha[200200], ark[200200], bought[200200];
ll c[200200];
set < pll > ms, ar, both, used;

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &c[i]);

    scanf("%d", &a);
    for (int i = 0; i < a; i++) {
        scanf("%d", &x);
        masha[x] = true;
    }
    scanf("%d", &b);
    for (int i = 0; i < b; i++) {
        scanf("%d", &x);
        ark[x] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (masha[i] && ark[i]) both.insert(pll(c[i], i));
        else if (masha[i]) ms.insert(pll(c[i], i));
        else if (ark[i]) ar.insert(pll(c[i], i));
    }
    while (ms.size() > k) ms.erase(*ms.rbegin());
    while (ar.size() > k) ar.erase(*ar.rbegin());

    while (!both.empty()) {
        pll x = *both.begin();
        both.erase(both.begin());

        if (ms.size() + used.size() < k && ar.size() + used.size() < k) {
            used.insert(x);
        }
        else if (ms.size() + used.size() < k) {
            used.insert(x);
            ar.erase(*ar.rbegin());
        }
        else if (ar.size() + used.size() < k) {
            used.insert(x);
            ms.erase(*ms.rbegin());
        }
        else if (x.first < (*ms.rbegin()).first + (*ar.rbegin()).first) {
            ms.erase(*ms.rbegin());
            ar.erase(*ar.rbegin());
            used.insert(x);
        }
        else {
            break;
        }
    }

    for (auto v : ms)
        printf("%lld %d\n", v.first, v.second);
    for (auto v : ar)
        printf("%lld %d\n", v.first, v.second);
    for (auto v : used)
        printf("%lld %d\n", v.first, v.second);

    if (ms.size() + used.size() < k || ar.size() + used.size() < k) printf("-1\n");
    else if (ms.size() + used.size() + ar.size() > m) printf("-1\n");
    else {
        ll ans = 0, cont = 0;
        for (auto v : ms) {
            ans += v.first;
            bought[v.second] = true;
            cont++;
        }

        for (auto v : ar) {
            ans += v.first;
            bought[v.second] = true;
            cont++;
        }

        for (auto v : used) {
            ans += v.first;
            bought[v.second] = true;
            cont++;
        }

        multiset < ll > left;
        for (int i = 1; i <= n; i++)
            if (!bought[i])
                left.insert(c[i]);

        for (auto v : left)
            printf("%lld ", v);
        printf("\n");

        while (cont < m) {
            ans += *left.begin();
            left.erase(left.begin());
            cont++;
        }
        printf("%lld\n", ans);
    }

    return 0;
}

