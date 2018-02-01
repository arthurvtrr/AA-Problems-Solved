#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <bitset>

using namespace std;

int n, m, r, c;
char T[440][440], P[440][440];
bitset <440> ans[440], G[30][440];

bitset <440> shift(bitset <440> b, int pos) {
    return b >> pos | b << (m-pos);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", T[i]);

    scanf("%d %d", &r, &c);
    for (int i = 0; i < r; i++)
        scanf("%s", P[i]);

    for (int i = 0; i < 440; i++)
        ans[i].set();

    for (int i = 0; i < 26; i++)
        for (int x = 0; x < n; x++)
            for (int y = 0; y < m; y++)
                G[i][x].set(y, T[x][y] == i + 'a');

    for (int x = 0; x < r; x++)
        for (int y = 0; y < c; y++) {
            char aux = P[x][y];
            if (aux == '?') continue;

            for (int i = 0; i < n; i++)
                ans[i] &= shift(G[aux - 'a'][(i+x) % n], y % m);
        }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << ans[i][j];
        printf("\n");
    }

    return 0;
}
