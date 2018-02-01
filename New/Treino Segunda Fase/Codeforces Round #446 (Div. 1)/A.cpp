#include <bits/stdc++.h>

using namespace std;

int n, nums[2020];

int main() {
    int ans = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        if (nums[i] == 1) ans++;
    }

    if (ans != 0) {
        printf("%d\n", n-ans);
        return 0;
    }

    ans = INT_MAX;

    for (int i = 0; i < n; i++) {
        int aux = nums[i];
        for (int j = i+1; j < n; j++) {
            aux = __gcd(aux, nums[j]);
            if (aux == 1) {
                ans = min(ans, j - i + n - 1);
                break;
            }
        }
    }

    printf("%d\n", ans == INT_MAX? -1 : ans);
    return 0;
}
