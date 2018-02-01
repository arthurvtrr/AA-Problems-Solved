#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define SIZ 2000

int n, q, x, y, ms[1 << 17], ans[1 << 19];
ll nums[1 << 17], hp[1 << 17], aux[1 << 17][20];

struct query {
    int x, y;
} qs[1 << 19];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);
    scanf("%d", &q);

    for (int i = 0; i < 1 << 17; i++) {
        int b = -1;
        for (int j = 17; j >= 0; j--)
            if (i & (1 << j)) {
                b = j;
                break;
            }
        ms[i] = b+1;
    }

    int lst = 1;
    for (int i = 1; i <= q; i++) {
        scanf("%d %d", &qs[i].x, &qs[i].y);
        qs[i].x %= 1 << 17;
        aux[qs[i].x][ms[qs[i].x]] += qs[i].y;

        if (i % SIZ == 0 || i == q) {
            for (int j = 0; j < 1 << 17; j++)
                hp[j] = nums[j];

            vector < int > died;

            for (int j = (1 << 17) - 1; j >= 0; j--) {
                for (int k = 17; k >= 0; k--)
                    hp[j] -= aux[j][k];

                for (int k = 16; k >= 0; k--) {
                    if (aux[j][k+1] == 0) continue;

                    aux[j - (1 << k)][ms[j % (1 << k)]] += aux[j][k+1];
                    aux[j][ms[j % (1 << k)]] += aux[j][k+1];
                }
                if (nums[j] > 0 && hp[j] <= 0) died.push_back(j);
            }

            for (int v : died) {
                int atual = nums[v];
                for (int j = lst; j <= i; j++)
                    if ((qs[j].x & v) == v) {
                        atual -= qs[j].y;
                        if (atual > 0) continue;
                        ans[j]--;
                        break;
                    }
            }

            for (int j = 0; j < 1 << 17; j++)
                nums[j] = hp[j];
            memset(aux, 0, sizeof aux);
            lst = i+1;
        }
    }

    int res = n;
    for (int i = 1; i <= q; i++) {
        res += ans[i];
        printf("%d\n", res);
    }

    return 0;
}
