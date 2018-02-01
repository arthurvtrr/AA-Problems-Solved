#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t;
ll n, nums[100100], suf[100100];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        ll x = (1LL << 32), y = x % (n+1);

        for (ll i = 0; i < n; i++)
            nums[i] = x / (n+1);
        for (ll i = n - y + 2; i < n; i++)
            nums[i]++;
        nums[0] -= 2;
        nums[1] += 2;

        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            printf("%d", nums[i]);
        }
        printf("\n");
    }

    return 0;
}
