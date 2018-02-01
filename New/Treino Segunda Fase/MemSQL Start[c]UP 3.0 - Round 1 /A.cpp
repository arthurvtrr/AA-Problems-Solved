#include <bits/stdc++.h>

using namespace std;

int n, nums[30];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    sort(nums, nums+n);
    printf("%d\n", max(0, nums[n-1] - 25));

    return 0;
}
