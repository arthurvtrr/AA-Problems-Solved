#include <bits/stdc++.h>

using namespace std;

int m, nums[1010], ans[4040];

int main() {
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < 3*m; i++)
        ans[i] = nums[0];

    int pos = 1;
    for (int i = 0; i < m; i++) {
        if (nums[i] % nums[0]) {
            printf("-1\n");
            return 0;
        }
        ans[pos] = ans[pos+1] = nums[i];
        pos += 3;
    }
    printf("%d\n", 3*m);
    for (int i = 0; i < 3*m; i++) {
        if (i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");

    return 0;
}
