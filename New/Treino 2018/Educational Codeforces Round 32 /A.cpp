#include <bits/stdc++.h>

using namespace std;

int n, nums[1010];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    int ans = 0;
    for (int i = 1; i < n-1; i++)
        if ((nums[i] < nums[i-1] && nums[i] < nums[i+1]) || (nums[i] > nums[i-1] && nums[i] > nums[i+1]))
            ans++;
    printf("%d\n", ans);

    return 0;
}
