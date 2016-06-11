#include <stdio.h>
#include <algorithm>

using namespace std;

int n, nums[1100], quant[101000];

int main() {
    while(1) {
        for (int i = 0; i < 101000; i++)
            quant[i] = 0;
        quant[0] = 1;

        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        for (int i = 0; i < n; i++)
            for (int j = 100999; j >= 0; j--)
                if (quant[j] != 0)
                    quant[j+nums[i]]++;

        int sol = 0;
        for (int i = 100999; i >= 0; i--)
            if (quant[i] >= 2) {
                sol = i;
                break;
            }
        printf("%d\n", sol);
    }
    return 0;
}
