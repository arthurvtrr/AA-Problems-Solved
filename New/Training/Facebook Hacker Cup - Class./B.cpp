#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int t, n, nums[110];

int main() {
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        sort(nums, nums+n);

        int ini = 0, fim = n-1, sol = 0;
        while (ini <= fim) {
            int need = 50 / nums[fim];
            need += 50 % nums[fim] != 0;

            if (need <= fim - ini + 1) sol++;

            ini += need-1;
            fim--;
        }

        printf("Case #%d: %d\n", tc+1, sol);
    }

    return 0;
}
