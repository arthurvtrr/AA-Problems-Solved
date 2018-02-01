#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, nums[100100], cont[100100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < n; i++) {
        int sqr = sqrt(nums[i]);

        for (int j = 1; j <= sqr; j++)
            if (nums[i] % j == 0) {
                cont[j]++;
                if (j*j != nums[i])
                    cont[nums[i] / j]++;
            }
    }

    int maxi = 1;
    for (int i = 2; i < 100100; i++)
        maxi = max(maxi, cont[i]);
    printf("%d\n", maxi);

    return 0;
}

