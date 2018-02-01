#include <bits/stdc++.h>

using namespace std;

int n, k, nums[110];

int main() {
    scanf("%d %d", &n, &k);

    int acum = 0, atual = 0, days = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        acum += nums[i];

        atual += min(8, acum);
        acum -= min(8, acum);
        days++;
        if (atual >= k) break;
    }
    printf("%d\n", atual < k? -1 : days);

    return 0;
}
