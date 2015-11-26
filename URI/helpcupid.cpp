#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, nums[1100];
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);
        sort(nums, nums+n);
        nums[n] = nums[0];
        int sol, val1 = 0, val2 = 0;
        for (int i = 0; i < n-1; i+=2) {
            val1 += min(nums[i+1]-nums[i], 24 - (nums[i+1]-nums[i]));
            val2 += min(abs(nums[i+2]-nums[i+1]), 24 - abs(nums[i+2]-nums[i+1]));
        }
        sol = min(val1, val2);
        printf("%d\n", sol);
    }
    return 0;
}
