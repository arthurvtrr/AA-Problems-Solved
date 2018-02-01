#include <bits/stdc++.h>

using namespace std;

int n, k, ns[100100], ks[200200];
bool valid[100100];

struct cp {
    int num, ind;
} cps[100100];

bool cmp(cp a, cp b) {
    return a.num < b.num;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ns[i]);
        cps[i].num = ns[i];
        cps[i].ind = i;
    }

    sort(cps, cps+n, cmp);

    for (int i = 0; i < k; i++)
        scanf("%d", &ks[i]);

    int ini = 0, fim = n-1;
    while (ini <= fim) {
        int mid = (ini + fim) / 2;
        memset(valid, 0, sizeof valid);

        int pos[2] = {0, n-1}, ind = 1;
        for (int i = 0; i < mid; i++) {
            valid[cps[pos[ind]].ind] = true;

            if (ind == 1) pos[ind]--;
            else pos[ind]++;

            ind = 1 - ind;
        }

        bool f = true;

        int last = 0;
        for (int i = 0; i < n; i++) {
            if (valid[i]) continue;
            if (ns[i] < last) f = false;
            last = ns[i];
        }

        if (f) fim = mid-1;
        else ini = mid+1;
    }

    if (ini > k) printf("-1\n");
    else printf("%d\n", ini);

    return 0;
}

