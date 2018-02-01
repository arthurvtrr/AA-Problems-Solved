#include <bits/stdc++.h>

using namespace std;

#define SIZ 450

int n, q, l, r, x, y, nums[200200], ans[200200];
int ini[SIZ][110], fim[SIZ][110], prv[200200], nxt[200200];

void update(int l, int r, int x, int y, int t) {
    int ind;

    if (t == 0) ind = l/SIZ;
    else ind = r/SIZ;

    vector < int > a, b;
    int aux = ini[ind][x];
    while (aux != -1) {
        if (aux >= l && aux <= r) a.push_back(aux);
        else b.push_back(aux);
        aux = nxt[aux];
    }

    for (int j = 0; j < a.size(); j++) {
        prv[a[j]] = nxt[a[j]] = -1;

        if (ini[ind][y] == -1) {
            ini[ind][y] = a[j];
            fim[ind][y] = a[j];
        }
        else {
            nxt[fim[ind][y]] = a[j];
            prv[a[j]] = fim[ind][y];
            fim[ind][y] = a[j];
        }
    }

    ini[ind][x] = fim[ind][x] = -1;

    for (int j = 0; j < b.size(); j++) {
        prv[b[j]] = nxt[b[j]] = -1;

        if (ini[ind][x] == -1) {
            ini[ind][x] = b[j];
            fim[ind][x] = b[j];
        }
        else {
            nxt[fim[ind][x]] = b[j];
            prv[b[j]] = fim[ind][x];
            fim[ind][x] = b[j];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    memset(ini, -1, sizeof ini);
    memset(fim, -1, sizeof fim);
    memset(prv, -1, sizeof prv);
    memset(nxt, -1, sizeof nxt);

    for (int i = 0; i < n; i++) {
        if (ini[i/SIZ][nums[i]] == -1) {
            ini[i/SIZ][nums[i]] = i;
            fim[i/SIZ][nums[i]] = i;
        }
        else {
            nxt[fim[i/SIZ][nums[i]]] = i;
            prv[i] = fim[i/SIZ][nums[i]];
            fim[i/SIZ][nums[i]] = i;
        }
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d %d", &l, &r, &x, &y);
        if (x == y) continue;

        l--; r--;

        if (l/SIZ == r/SIZ) {
            update(l, r, x, y, 0);
        }
        else {
            for (int j = l/SIZ+1; j < r/SIZ; j++) {
                if (ini[j][x] == -1) continue;

                if (ini[j][y] == -1) {
                    ini[j][y] = ini[j][x];
                    fim[j][y] = fim[j][x];
                }
                else {
                    nxt[fim[j][y]] = ini[j][x];
                    prv[ini[j][x]] = fim[j][y];
                }

                fim[j][y] = fim[j][x];
                ini[j][x] = fim[j][x] = -1;
            }

            update(l, r, x, y, 0);
            update(l, r, x, y, 1);
        }
    }

    for (int i = 0; i < SIZ; i++) {
        for (int j = 0; j < 110; j++) {
            int x = ini[i][j];
            while (x != -1) {
                ans[x] = j;
                x = nxt[x];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
