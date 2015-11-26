#include <stdio.h>
#include <vector>

using namespace std;

int n;
int nums[2200] = {0};

int main() {
    scanf("%d", &n);

    int x;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        nums[x]++;
    }

    for (int i = 0; i < 2100; i++) {
        if (nums[i] != 0)
            printf("%d aparece %d vez(es)\n", i, nums[i]);
    }

    return 0;
}
