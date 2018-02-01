#include <bits/stdc++.h>

using namespace std;

int n, nums[1100];
set < int > ps;
int main() {
    for (int i = 0; i < 1100; i++)
        ps.insert(i*i);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
        if (!ps.count(nums[i]))
            ans = max(ans, nums[i]);
    printf("%d\n", ans);

    return 0;
}
