#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, nums[110];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    sort(nums, nums+n);

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", nums[i]);
    }
    printf("\n");
    return 0;
}
