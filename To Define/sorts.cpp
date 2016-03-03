#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int nums[3], ord[3];

    for (int i = 0; i < 3; i++) {
        scanf("%d", &nums[i]);
        ord[i] = nums[i];
    }

    sort(ord, ord+3);

    for (int x : ord)
        printf("%d\n", x);

    printf("\n");

    for (int x : nums)
        printf("%d\n", x);

    return 0;
}
