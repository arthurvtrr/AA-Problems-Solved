#include <bits/stdc++.h>

using namespace std;

int n, nums[110];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        nums[i] += nums[i-1];
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            ans = max(ans, nums[n] - (nums[j] - nums[i-1]) + (j-i+1) - (nums[j] - nums[i-1]));

    printf("%d\n", ans);
    return 0;
}
