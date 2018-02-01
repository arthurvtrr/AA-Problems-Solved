#include <bits/stdc++.h>

using namespace std;

int n, nums[100100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int ans = 0, last = nums[0];
    for (int i = 1; i < n; i++) {
        if ((nums[i] + last) % 2 == 0) ans++;
        else last = nums[i];
    }

    printf("%d\n", ans);

    return 0;
}

