#include <bits/stdc++.h>

#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

using namespace std;

int n, m, aux, x, c, app[2][17000];
bool used[17000];

struct subset {
    int par, rank;
} subsets[17000];

int Find(int u) {
    if (u != subsets[u].par) subsets[u].par = Find(subsets[u].par);
    return subsets[u].par;
}

void Union(int x, int y) {
    int rx = Find(x), ry = Find(y);
    if (subsets[rx].rank < subsets[ry].rank)
        subsets[rx].par = ry;
    else if (subsets[rx].rank > subsets[ry].rank)
        subsets[ry].par = rx;
    else {
        subsets[ry].par = rx;
        subsets[rx].rank++;
    }
}

int val(char c) {
    if (c <= '9') return (c - '0');
    return (c - 'A') + 10;
}

int main() {
    scanf("%d %d", &n, &m);

    memset(app, -1, sizeof app);

    int ans = 0, cmp = 0, ind = 0;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            for (int j = 0; j < m/4; j++) {
                scanf(" %c", &aux);
                x = val(aux);
                for (int k = 3; k >= 0; k--) {
                    if (x & (1 << k)) {
                        if (ind && app[0][ind-1] != -1) app[0][ind] = app[0][ind-1];
                        else {
                            used[cmp] = true;
                            app[0][ind] = cmp++;
                            ans++;
                        }
                    }

                    ind++;
                }
            }
        }
        else {
            memset(app[1], -1, sizeof app[1]);

            for (int j = 0; j <= m; j++) {
                subsets[j].par = j;
                subsets[j].rank = 1;
            }

            ind = 0, cmp = 0;
            for (int j = 0; j < m/4; j++) {
                scanf(" %c", &aux);
                x = val(aux);
                for (int k = 3; k >= 0; k--) {
                    if (x & (1 << k)) {
                        if (ind && app[1][ind-1] != -1) app[1][ind] = app[1][ind-1];
                        else {
                            while (used[cmp]) cmp++;
                            app[1][ind] = cmp++;
                            ans++;
                        }
                    }
                    ind++;
                }
            }

            memset(used, 0, sizeof used);

            for (int j = 0; j < m; j++) {
                if (app[1][j] == 0 && app[0][j] != -1) {
                    int pos = j;
                    while (pos >= 0 && app[1][pos] == 0) {
                        app[1][pos] = app[0][j];
                        pos--;
                    }

                    pos = j+1;
                    while (pos < m && app[1][pos] == 0) {
                        app[1][pos] = app[0][j];
                        pos++;
                    }
                    ans--;
                }
                else if (app[1][j] > 0 && app[0][j] != -1 && app[0][j] != app[1][j]) {
                    if (Find(app[1][j]) != Find(app[0][j])) {
                        Union(app[1][j], app[0][j]);
                        ans--;
                    }
                }
            }

            for (int j = 0; j < m; j++) {
                app[0][j] = app[1][j] > 0? Find(app[1][j]) : app[1][j];
                if (app[0][j] != -1) used[app[0][j]] = true;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}
