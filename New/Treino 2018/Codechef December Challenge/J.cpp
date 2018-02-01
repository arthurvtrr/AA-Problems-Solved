#include <bits/stdc++.h>

using namespace std;

int t, k, n, aux[100100];

struct cand {
    int p, s;
} cands[11];

bool cmp1(cand a, cand b) {
    return a.s < b.s;
}

struct ord {
    int d, m;
} ords[55];

bool cmp2(ord a, ord b) {
    return a.m < b.m;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &k);
        for (int i = 0; i < k; i++)
            scanf("%d %d", &cands[i].p, &cands[i].s);
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d %d", &ords[i].d, &ords[i].m);

        if (n == 1) {
            int ans = INT_MAX;
            for (int i = 0; i < k; i++)
                if (ords[0].d <= ords[0].m * cands[i].p)
                    ans = min(ans, cands[i].s);
            printf("%d\n", ans == INT_MAX? -1 : ans);
        }
        else {
            sort(cands, cands+k, cmp1);
            sort(ords, ords+n, cmp2);

            int cost = 0;
            for (int lst = 0; lst < k; lst++) {
                memset(aux, 0, sizeof aux);

                cost += cands[lst].s;
                bool valid = true;

                for (int i = 0; i < n; i++) {
                    int lft = ords[i].d;
                    set < int > used;
                    for (int j = 0; j <= lst; j++) {
                        for (int pos = 1; pos <= ords[i].m * cands[0].p; pos++)
                            if (aux[pos] == j && !used.count(pos)) {
                                aux[pos]++;
                                used.insert(pos);
                                lft--;
                                if (lft == 0) break;
                            }
                        if (lft == 0) break;
                    }
                    if (lft) valid = false;
                }

                if (valid) {
                    printf("%d\n", cost);
                    break;
                }
                else if (lst == k-1) printf("-1\n");
            }
        }
    }

    return 0;
}
