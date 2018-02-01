#include <bits/stdc++.h>

using namespace std;

int n, nums[100100];
map < int, int > pos;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        pos[nums[i]] = i;
    }
    sort(nums, nums+n);

    long long ans = 0;
    for (int i = 1; i < n; i++) {
        int a = pos[nums[i-1]], b = pos[nums[i]];
        if (a < b) ans += min(b - a, a + n - b);
        else ans += min(a - b, b + n - a);
    }
    printf("%lld\n", ans);

    return 0;
}


