#include <bits/stdc++.h>

using namespace std;

int n, k, nums[110];

int main() {
    scanf("%d %d", &n, &k);

    int used = 0;
    for (int i = 0; i < k; i++) {
        scanf("%d", &nums[i]);
        while (used < 4*n && nums[i] >= 4) {
            nums[i] -= 4;
            used += 4;
        }
    }

    int leftd = (4*n - used) / 4 + 2*n;
    for (int i = 0; i < k; i++) {
        while (leftd && nums[i] >= 2) {
            nums[i] -= 2;
            leftd--;
        }
    }

    int rest = 0;
    for (int i = 0; i < k; i++)
        rest += nums[i];

    if (leftd + (4*n - used) / 4 < rest) printf("NO\n");
    else printf("YES\n");

    return 0;
}
