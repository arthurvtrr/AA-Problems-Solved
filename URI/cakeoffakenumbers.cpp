#include <stdio.h>
#include <algorithm>

using namespace std;

bool found(int *nums, int n) {
    for (int i = 0; i < n; i++)
        if (nums[i] != i) return false;
    return true;
}

int main() {
    int n, nums[1100];
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int need = n - nums[0];
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            nums[i] += need;
            nums[i] %= n;
        } else {
            nums[i] = n - (need - nums[i]);
            nums[i] %= n;
        }
    }

    if (found(nums, n)) printf("Yes\n");
    else printf("No\n");

    return 0;
}
