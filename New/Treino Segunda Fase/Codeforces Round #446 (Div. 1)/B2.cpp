#include <bits/stdc++.h>

using namespace std;

int n, nums[1000100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int lst = n, ans = 0;
    for (int i = n-1; i >= 0; i--) {
        if (i < lst) ans++;
        lst = min(lst, i-nums[i]);
    }
    printf("%d\n", ans);

    return 0;
}
