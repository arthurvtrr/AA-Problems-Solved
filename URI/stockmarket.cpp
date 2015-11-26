#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, c, nums[220000], sol;
    while (scanf("%d %d", &n, &c) != EOF) {
        sol = 0;
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        int now = 0, maxi = 0;
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[now] && maxi == now) {
                now = ++maxi;
                i = maxi;
            }
            else if (nums[i] < nums[maxi] && nums[maxi] - nums[i] > c) {
                if (maxi != now) sol += nums[maxi] - nums[now] - c;
                i = ++maxi;
                now = maxi;
            }
            else if (nums[i] > nums[now] + c && nums[i] > nums[maxi]) maxi = i;
        }
        if (maxi != now) sol += nums[maxi] - nums[now] - c;
        printf("%d\n", sol);
    }
    return 0;
}
