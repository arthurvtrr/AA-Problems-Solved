#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n;
ll nums[55];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll aux = nums[i];
        while (aux > 0) {
            ans += aux / n;
            aux = (aux % n) + aux / n - 1;
        }
        aux = nums[i] / n;
        while (aux > 0) {
            ans += (aux / n) * (n-1);
            aux = (aux % n) + aux / n - 1;
        }
    }
    printf("%lld\n", ans);

    return 0;
}

