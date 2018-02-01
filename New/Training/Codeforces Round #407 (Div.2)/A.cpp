#include <bits/stdc++.h>

using namespace std;

int n, k, nums[100100];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += (nums[i] + k - 1) / k;

    printf("%d\n", (ans + 1) / 2);

    return 0;
}
