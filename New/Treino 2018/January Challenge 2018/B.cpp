#include <bits/stdc++.h>

using namespace std;

int t, n, nums[770][770];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &nums[i][j]);

        for (int i = 0; i < n; i++)
            sort(nums[i], nums[i]+n);

        int lst = INT_MAX;
        long long ans = 0;
        for (int i = n-1; i >= 0; i--) {
            int pos = n-1;
            while (pos >= 0 && nums[i][pos] >= lst) pos--;
            if (pos == -1) { ans = -1; break; }
            else { ans += nums[i][pos]; lst = nums[i][pos]; }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
