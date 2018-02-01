#include <bits/stdc++.h>

using namespace std;

int n, nums[100100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    long long ans = 0;
    int last = 0, energy = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] - last > energy) {
            ans += nums[i] - last - energy;
            last = nums[i];
            energy = 0;
        }
        else {
            energy += last - nums[i];
            last = nums[i];
        }
    }

    printf("%lld\n", ans);

    return 0;
}
