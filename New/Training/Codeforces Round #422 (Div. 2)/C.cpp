#include <bits/stdc++.h>

using namespace std;

int n, x;

struct vouc {
    int l, r, c;
} vouchs[200200];

vector < int > tim[200200], mini[200200];

bool cmp(int a, int b) {
    return vouchs[a].l < vouchs[b].l;
}

int main() {
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &vouchs[i].l, &vouchs[i].r, &vouchs[i].c);
        tim[vouchs[i].r - vouchs[i].l + 1].push_back(i);
    }

    for (int i = 0; i < 200200; i++) {
        sort(tim[i].begin(), tim[i].end(), cmp);

        for (int j = 0; j < tim[i].size(); j++)
            mini[i].push_back(vouchs[tim[i][j]].c);

        for (int j = (int)tim[i].size() - 2; j >= 0; j--)
            mini[i][j] = min(mini[i][j], mini[i][j+1]);
    }

    int ans = INT_MAX;

    for (int i = 0; i < n; i++) {
        int lft = x - (vouchs[i].r - vouchs[i].l + 1);
        if (lft < 0) continue;

        int ini = 0, fim = (int)tim[lft].size() - 1;
        while (ini <= fim) {
            int mid = (ini + fim) / 2;
            if (vouchs[tim[lft][mid]].l <= vouchs[i].r) ini = mid + 1;
            else fim = mid - 1;
        }

        if (ini >= tim[lft].size()) continue;

        ans = min(ans, vouchs[i].c + mini[lft][ini]);
    }

    printf("%d\n", ans == INT_MAX? -1 : ans);

    return 0;
}

