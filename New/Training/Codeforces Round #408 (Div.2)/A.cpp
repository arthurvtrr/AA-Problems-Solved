#include <bits/stdc++.h>

using namespace std;

int n, m, k, prices[110];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &prices[i]);

    int min_dist = 10000000;

    for (int i = m-1; i > 0; i--)
        if (prices[i] > 0 && prices[i] <= k)
            min_dist = min(min_dist, (m-i)*10);

    for (int i = m+1; i <= n; i++)
        if (prices[i] > 0 && prices[i] <= k)
            min_dist = min(min_dist, (i-m)*10);

    printf("%d\n", min_dist);

    return 0;
}
