#include <bits/stdc++.h>

using namespace std;

int n, k, nums[100100];

int main() {
    while (scanf("%d %d", &n, &k) != EOF) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &nums[i]);
            sum += nums[i];
        }

        multiset < int > chosen;
        for (int i = 1; i <= n; i++) {
            if (i % (k+1) == 0) {
                chosen.insert(nums[i]);
            }
            else if (!chosen.empty() && nums[i] > *chosen.begin()) {
                chosen.erase(chosen.begin());
                chosen.insert(nums[i]);
            }
        }

        for (int v : chosen)
            sum -= v;
        printf("%d\n", sum);
    }
    return 0;
}
