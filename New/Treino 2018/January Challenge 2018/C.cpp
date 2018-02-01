#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t, n, k, nums[100100];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%d", &nums[i]);

        ll ibest = 0, isum = 0, ileft = nums[0], iright = nums[n-1], best = 0, sum = 0, left = 0, right = 0;

        ll atual = 0, b = nums[0];
        for (int i = 0; i < n; i++) {
            atual += nums[i];
            b = max(b, atual);
            if (atual <= 0) atual = 0;

            isum += nums[i];
        }
        ibest = b;

        atual = 0;
        for (int i = 0; i < n; i++) {
            atual += nums[i];
            ileft = max(ileft, atual);
        }

        atual = 0;
        for (int i = n-1; i >= 0; i--) {
            atual += nums[i];
            iright = max(iright, atual);
        }

        best = ibest; sum = isum; left = ileft; right = iright;
        for (int i = 0; i < k-1; i++) {
            ll s = sum + isum;
            ll l = max(left, sum + ileft);
            ll r = max(iright, isum + right);
            ll b = max({l, r, best, ibest, right + ileft});

            best = b; sum = s; left = l, right = r;
        }
        printf("%lld\n", best);

    }
    return 0;
}
