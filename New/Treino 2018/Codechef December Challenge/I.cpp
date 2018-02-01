#include <bits/stdc++.h>

using namespace std;

int t, n, nums[100100], cnt[100100], nw[100100], ans[100100];

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(cnt, 0, sizeof cnt);
        memset(nw, 0, sizeof nw);

        scanf("%d", &n);
        int quant = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
            cnt[nums[i]]++;
            if (cnt[nums[i]] == 2) quant++;
        }

        if (n <= 7) {
            int best = 0;
            for (int i = 0; i < n; i++)
                ans[i] = nums[i];
            sort(ans, ans+n);
            do {
                int aux = 0;
                for (int i = 0; i < n; i++)
                    aux += nums[i] != ans[i];
                best = max(best, aux);
            } while (next_permutation(ans, ans+n));

            sort(ans, ans+n);
            do {
                int aux = 0;
                for (int i = 0; i < n; i++)
                    aux += nums[i] != ans[i];
                if (aux == best) {
                    printf("%d\n", aux);
                    for (int i = 0; i < n; i++) {
                        if (i) printf(" ");
                        printf("%d", ans[i]);
                    }
                    printf("\n");
                    break;
                }
            } while (next_permutation(ans, ans+n));
        }
        else {
            printf("%d\n", n);

            int lst = -1, fst = -1;
            for (int i = 0; i < 100100; i++)
                if (cnt[i] == 2) {
                    if (fst == -1) fst = i;
                    if (lst != -1) nw[lst] = i;
                    lst = i;
                }
            nw[lst] = fst;

            lst = -1, fst = -1;
            for (int i = 0; i < 100100; i++)
                if (cnt[i] == 1) {
                    if (fst == -1) fst = i;
                    if (lst != -1) nw[lst] = i;
                    lst = i;
                }
            nw[lst] = fst;

            for (int i = 0; i < n; i++)
                ans[i] = nw[nums[i]];

            if (n - quant*2 == 1) {
                for (int i = 0; i < n; i++)
                    if (cnt[ans[i]] == 1)
                        swap(ans[i], i? ans[0] : ans[1]);
            }
            else if (quant == 1) {
                vector < int > pos;
                for (int i = 0; i < n; i++)
                    if (cnt[ans[i]] == 1) {
                        pos.push_back(i);
                        if (pos.size() == 2) break;
                    }

                for (int i = 0; i < n; i++)
                    if (cnt[ans[i]] == 2) {
                        int ind = 0, orig = ans[i];
                        for (int j = 0; j < n; j++)
                            if (ans[j] == orig)
                                ans[j] = ans[pos[ind++]];

                        ans[pos[0]] = ans[pos[1]] = orig;
                        break;
                    }
            }

            for (int i = 0; i < n; i++) {
                if (i) printf(" ");
                printf("%d", ans[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
