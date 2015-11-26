#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    int t, n, nums[100010];
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d", &n);
        memset(nums, 0, sizeof nums);
        for (int i = 2; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                nums[j] = nums[j] ^ 1;
            }
        }

        int sol = 0;
        for (int i = 1; i <= n; i++)
            if (nums[i] == 0) sol++;

        printf("%d\n", sol);
    }
    return 0;
}
