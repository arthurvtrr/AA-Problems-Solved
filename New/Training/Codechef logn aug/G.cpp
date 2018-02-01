#include <bits/stdc++.h>

using namespace std;

int n, q, t, x, y, z, nxt[2][100100];
long long nums[100100];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &nums[i]);

    for (int i = 1; i <= n; i++) {
        nxt[0][i] = i;
        for (int j = min(i+1, n); j <= min(i+100, n); j++)
            if (nums[j] > nums[i]) {
                nxt[0][i] = j;
                break;
            }
    }

    for (int i = 1; i <= n; i++) {
        int aux = i;
        for (int j = 0; j < 50; j++)
            aux = nxt[0][aux];
        nxt[1][i] = aux;
    }

    for (int i = 0; i < q; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &x, &y);

            while (y >= 50) {
                x = nxt[1][x];
                y -= 50;
            }
            while (y--) x = nxt[0][x];

            printf("%d\n", x);
        }
        else {
            scanf("%d %d %d", &x, &y, &z);

        }
    }
    return 0;
}
