#include <bits/stdc++.h>

using namespace std;

int n, nums[110];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    sort(nums, nums+n);
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", nums[i]);
    }
    printf("\n");

    return 0;
}


