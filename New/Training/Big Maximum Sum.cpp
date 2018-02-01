#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, m, l, x, ind[300300];

struct state {
    vector < int > nums;
    ll maxSum = 0, sum = 0, leftSum = 0, rightSum = 0;
} mini[55];

set < int > used;

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &l);
        for (int j = 0; j < l; j++) {
            scanf("%d", &x);
            mini[i].nums.push_back(x);
            mini[i].sum += x;
        }

        ll sum = 0, lsum = 0, rsum = 0;
        for (int j = 0; j < l; j++) {
            sum += mini[i].nums[j];
            lsum += mini[i].nums[j];
            if (sum < 0) {
                sum = 0;
                continue;
            }

            mini[i].maxSum = max(mini[i].maxSum, sum);
            mini[i].leftSum = max(mini[i].leftSum, lsum);
        }

        for (int j = l-1; j >= 0; j--) {
            rsum += mini[i].nums[j];
            mini[i].rightSum = max(mini[i].rightSum, rsum);
        }
    }

    for (int i = 0; i < m; i++) {
        scanf("%d", &ind[i]);
        used.insert(ind[i]);
    }

    ll ans = 0, sum = 0, lefts = 0, rights = 0;
    for (int i = 0; i < m; i++) {
        ll aux = rights;
        lefts = max(lefts, sum + mini[ind[i]].leftSum);
        rights = max(mini[ind[i]].rightSum, rights + mini[ind[i]].sum);
        ans = max({ans, lefts, rights, aux + mini[ind[i]].leftSum, mini[ind[i]].maxSum});
        sum += mini[ind[i]].sum;
    }

    if (ans <= 0) {
        ans = -1000000000;
        for (auto it : used)
            for (int i = 0; i < mini[it].nums.size(); i++)
                ans = max(ans, (ll) mini[it].nums[i]);
    }

    printf("%lld\n", ans);

    return 0;
}
