#include <bits/stdc++.h>

using namespace std;

int t, n, d;
long long nums[100100];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &d);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%lld", &nums[i]);
            sum += nums[i];
        }

        long long ans = 0, valid = 1;
        if (sum % n != 0) valid = 0;
        else {
            sum /= n;
            for (int i = 0; i < n-d; i++) {
                long long change = sum - nums[i];
                nums[i] += change;
                nums[i+d] -= change;
                ans += abs(change);
            }

            for (int i = 0; i < n; i++)
                if (nums[i] != sum)
                    valid = 0;
        }

        printf("%lld\n", valid? ans : -1);
    }
    return 0;
}
