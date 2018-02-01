#include <bits/stdc++.h>

using namespace std;

int n, nums[200100], acum[200100];

int main() {
    scanf("%d", &n);
    int black = 0, white = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        if (nums[i] == 1) black++;
        else white++;
    }

    for (int i = n+1; i <= 2*n; i++)
        nums[i] = nums[i-n];

    int ans = n;
    for (int i = 1; i <= 2*n; i++) {
        acum[i] = nums[i];
        acum[i] += acum[i-1];
    }

    for (int i = 1; i <= 2*n-black+1; i++)
        ans = min(ans, black - (acum[i+black-1] - acum[i-1]));

    printf("%d\n", ans);

    return 0;
}

