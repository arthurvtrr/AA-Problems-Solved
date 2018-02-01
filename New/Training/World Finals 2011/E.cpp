#include <bits/stdc++.h>

using namespace std;

int dx, dy, n, q, m;
int bit[2020][2020], posx[1010][1010], posy[1010][1010];

struct pt {
    int x, y;
} pts[500500];

void update(int x, int y, int val) {
    int y1;
    while (x < 2020) {
        y1 = y;
        while (y1 < 2020) {
            bit[x][y1] += val;
            y1 += (y1 & -y1);
        }
        x += (x & -x);
    }
}

int query(int x, int y) {
    int y1, result = 0;
    while (x) {
        y1 = y;
        while (y1) {
            result += bit[x][y1];
            y1 -= (y1 & -y1);
        }
        x -= (x & -x);
    }
    return result;
}

int main() {
    for (int i = 1; i <= 1000; i++) {
        int a = i, b = 1001-i;
        for (int j = 1; j <= 1000; j++) {
            posx[i][j] = a+j-1;
            posy[i][j] = b+j-1;
        }
    }

    int t = 1;
    while (1) {
        scanf("%d %d %d %d", &dx, &dy, &n, &q);
        if (dx + dy + n + q == 0) break;

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &pts[i].x, &pts[i].y);
            update(posx[pts[i].x][pts[i].y], posy[pts[i].x][pts[i].y], 1);
        }

        printf("Case %d:\n", t++);

        for (int i = 0; i < q; i++) {
            scanf("%d", &m);
            int maxi = 0, a = 1, b = 1;

            for (int j = 1; j <= dy; j++) {
                for (int k = 1; k <= dx; k++) {
                    int lx = max(0, posx[k][j] - m - 1), ly = max(0, posy[k][j] - m - 1);
                    int rx = min(2019, posx[k][j] + m), ry = min(2019, posy[k][j] + m);

                    int aux = 0;

                    aux += query(rx, ry); if (aux <= maxi) continue;
                    aux += query(lx, ly); if (aux <= maxi) continue;
                    aux -= query(rx, ly); if (aux <= maxi) continue;
                    aux -= query(lx, ry); if (aux <= maxi) continue;

                    maxi = aux; a = k; b = j;
                }
                if (maxi == n) break;
            }

            printf("%d (%d,%d)\n", maxi, a, b);
        }

        for (int i = 0; i < n; i++)
            update(posx[pts[i].x][pts[i].y], posy[pts[i].x][pts[i].y], -1);
    }

    return 0;
}

