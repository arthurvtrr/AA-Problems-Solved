#include <bits/stdc++.h>

using namespace std;

int n, k, nums[110];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        bool v = true;
        for (int j = 0; j < n; j++)
            if (j != i && abs(nums[i] - nums[j]) <= k) {
                v = false;
            }
        if (v) ans++;
    }
    printf("%d\n", ans);

    return 0;
}
