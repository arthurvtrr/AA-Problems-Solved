#include <bits/stdc++.h>

using namespace std;

int n, m, acum[100100], ans[100100], zeros[100100];

struct need {
    int l, r, q;
} needs[100100];

bool cmp(need a, need b) {
    if (a.l == b.l)
        return a.r < b.r;
    return a.l < b.l;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d %d %d", &needs[i].l, &needs[i].r, &needs[i].q);

    sort(needs, needs+m, cmp);

    bool possible = true;

    for (int i = 0; i < 30; i++) {
        for (int j = 0; j <= n; j++)
            acum[j] = zeros[j] = 0;

        int atual = 0;
        for (int j = 0; j < m; j++)
            if (needs[j].q & (1 << i)) {
                atual = max(atual, needs[j].l);
                while (atual <= needs[j].r)
                    acum[atual++] = 1;
            }

        for (int j = 1; j <= n; j++)
            acum[j] += acum[j-1];

        for (int j = 0; j < m; j++)
            if (!(needs[j].q & (1 << i))) {
                int ini = needs[j].l, fim = needs[j].r;
                while (ini <= fim) {
                    int mid = (ini + fim) / 2;

                    if (acum[mid] - acum[needs[j].l - 1] == mid - needs[j].l + 1) ini = mid+1;
                    else fim = mid-1;
                }

                if (ini == needs[j].r + 1) possible = false;
                else zeros[ini] = 1;
            }

        atual = 0;
        for (int j = 0; j < m; j++)
            if (needs[j].q & (1 << i)) {
                atual = max(atual, needs[j].l);
                while (atual <= needs[j].r) {
                    if (!zeros[atual])
                        ans[atual] |= 1 << i;
                    atual++;
                }
            }
    }

    if (!possible) printf("NO\n");
    else {
        printf("YES\n");
        for (int i = 1; i <= n; i++) {
            if (i > 1) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
