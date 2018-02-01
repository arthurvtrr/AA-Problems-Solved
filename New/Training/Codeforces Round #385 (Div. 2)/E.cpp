#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n;

struct card {
    char type;
    int r;
    int b;
} cards[20];

int dp[20][70000];

int solve(int id, int mask, int lefta, int leftb) {
    if (dp[id][mask] != -1)
        return dp[id][mask];

    if (mask == ((1 << n) - 1)) return 0;

    int ret = 1000000000;

    int a = 0, b = 0;

    for (int i = 0; i < n; i++)
        if (mask & (1 << i)) {
            if (cards[i].type == 'R') a++;
            else b++;
        }

    for (int i = 0; i < n; i++)
        if (!(mask & (1 << i))) {
            int cost = max(max(cards[i].r - a, 0) - lefta, max(cards[i].b - b, 0) - leftb);
            cost = max(cost, 0);

            ret = min(ret, cost + solve(i, mask | (1 << i), lefta + cost - max(cards[i].r - a, 0), leftb + cost - max(cards[i].b - b, 0)));
        }

    return dp[id][mask] = ret;
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf(" %c %d %d", &cards[i].type, &cards[i].r, &cards[i].b);

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 70000; j++)
            dp[i][j] = -1;

    printf("%d\n", solve(0, 0, 0, 0) + n);
    return 0;
}
