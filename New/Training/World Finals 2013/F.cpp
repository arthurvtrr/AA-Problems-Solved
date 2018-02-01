#include <bits/stdc++.h>

using namespace std;

int n, k, nums[1001000];

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < 2*n*k; i++)
        scanf("%d", &nums[i]);
    sort(nums, nums+2*n*k);

    int ini = 0, fim = 1000000000;
    while (ini <= fim) {
        int mid = (ini + fim) / 2;

        int chosen = 1;
        for (int i = 3; i < 2*n*k; i++) {
            if (chosen == n) break;

            if (nums[i] - nums[i-1] <= mid) { chosen++; i++; }
            else if (i - 1 == 2*k*chosen) break;
        }

        if (chosen != n || nums[1] - nums[0] > mid) ini = mid+1;
        else fim = mid-1;
    }
    printf("%d\n", ini);

    return 0;
}

