#include <stdio.h>
#include <algorithm>

using namespace std;

bool comp(int x, int y) {
    return x > y;
}

int main() {
    int n, x, nums[1100], y;
    for (int i = 0; i < 1100; i++) nums[i] = 0;
    scanf("%d", &n);
    scanf("%d", &x);
    for (int i = 1; i < n; i++) {
        scanf("%d", &y);
        nums[y]++;
    }

    int sol = 0;
    for (int i = 1010; i > 0; i--) {
        while (nums[i] > 0 && i >= x) {
            nums[i]--;
            nums[i-1]++;
            x++;
            sol++;
        }
    }

    printf("%d\n", sol);
    return 0;
}
