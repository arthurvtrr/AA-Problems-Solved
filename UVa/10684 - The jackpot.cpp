#include <stdio.h>
#include <algorithm>

using namespace std;

int n, nums[11000];

int main() {
    while (scanf("%d", &n), n) {
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        int maxi = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            if (sum < 0)
                sum = 0;
            maxi = max(maxi, sum);
        }

        if (maxi > 0) printf("The maximum winning streak is %d.\n", maxi);
        else printf("Losing streak.\n");
    }
    return 0;
}
