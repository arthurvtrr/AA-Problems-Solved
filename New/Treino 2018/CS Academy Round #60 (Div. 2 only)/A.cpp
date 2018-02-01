#include <bits/stdc++.h>

using namespace std;

int n, nums[110];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);
    sort(nums, nums+n);
    int sum = 0;
    for (int i = 1; i < n-1; i++)
        sum += nums[i];
    printf("%d\n", sum / (n-2));

    return 0;
}
