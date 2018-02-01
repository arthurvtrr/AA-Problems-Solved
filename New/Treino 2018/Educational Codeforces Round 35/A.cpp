#include <bits/stdc++.h>

using namespace std;

int n, nums[100100];

int main() {
    scanf("%d", &n);
    int mini = INT_MAX;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        mini = min(mini, nums[i]);
    }
    int ans = n-1, lst = -1;
    for (int i = 0; i < n; i++)
        if (nums[i] == mini) {
            if (lst != -1) ans = min(ans, i - lst);
            lst = i;
        }
    printf("%d\n", ans);

    return 0;
}
