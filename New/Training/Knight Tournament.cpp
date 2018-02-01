#include <bits/stdc++.h>

using namespace std;

int n, m, ans[300300];

struct fight {
    int l, r, x;
} fights[300300];

set < int > knights;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &fights[i].l, &fights[i].r, &fights[i].x);

    for (int i = 1; i <= n; i++)
        knights.insert(i);

    for (int i = 0; i < m; i++) {
        vector < int > rem;

        auto x = knights.lower_bound(fights[i].l);
        auto y = knights.lower_bound(fights[i].r);
        if (*y == fights[i].r) y++;

        for (auto a = x; a != y; a++)
            if (*a != fights[i].x) {
                ans[*a] = fights[i].x;
                rem.push_back(*a);
            }

        for (int j = 0; j < rem.size(); j++)
            knights.erase(rem[j]);
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
