#include <bits/stdc++.h>

using namespace std;

int n;
long long nums[300300];

long long func(long long x) {
    long long ret = 0;
    for (int i = 0; i < n; i++)
        ret += abs(x - nums[i]);
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);

    long long left = -10000000000LL, right = 10000000000LL;
    int iter = 200;
    while (iter--) {
        long long lt = (2LL*left + right) / 3LL;
        long long rt = (left + 2LL*right) / 3LL;

        if (func(lt) > func(rt)) left = lt;
        else right = rt;
    }

    long long ans = left-2;
    for (long long i = left-2; i <= right+2; i++)
        if (func(i) < func(ans))
            ans = i;

    printf("%lld\n", ans);

    return 0;
}
