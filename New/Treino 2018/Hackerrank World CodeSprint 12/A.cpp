#include <bits/stdc++.h>

using namespace std;

int t, n, nums[55];

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        sort(nums, nums+n);

        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            ans = min(2*(nums[i] - nums[0]) + nums[n-1] - nums[i], ans);
            ans = min(nums[i] - nums[0] + 2*(nums[n-1] - nums[i]), ans);
        }
        printf("%d\n", ans);
    }

    return 0;
}
