#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n;
ll d, nums[100100], sum[100100], maxi[100100];

int main() {
    scanf("%d %lld", &n, &d);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &nums[i]);
        sum[i] = nums[i];
        if (i) sum[i] += sum[i-1];
    }

    for (int i = 0; i < n; i++)
        if (sum[i] > d) {
            printf("-1\n");
            return 0;
        }

    for (int i = 0; i < n; i++)
        maxi[i] = sum[i];

    for (int i = n-2; i >= 0; i--)
        maxi[i] = max(maxi[i], maxi[i+1]);

    ll add = 0, ans = 0;
    for (int i = 0; i < n; i++)
        if (nums[i] == 0 && sum[i] + add < 0) {
            ll need = d - maxi[i] - add;
            add += need;
            ans++;

            if (sum[i] + add < 0) {
                printf("-1\n");
                return 0;
            }
        }

    printf("%lld\n", ans);

    return 0;
}

