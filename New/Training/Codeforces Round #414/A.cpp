#include <bits/stdc++.h>

using namespace std;

int a, b, c, n, nums[100100];

int main() {
    scanf("%d %d %d", &a, &b, &c);
    scanf("%d", &n);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        if (nums[i] > b && nums[i] < c) ans++;
    }
    printf("%d\n", ans);

    return 0;
}
