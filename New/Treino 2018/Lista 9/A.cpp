#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define INF 1000000

int n;
ll s, nums[200200], acum[200200], sum;

int main() {
    scanf("%d %lld", &n, &s);
    sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &nums[i]);
        acum[i] = nums[i];
        sum += nums[i];
    }

    if (sum <= s) {
        printf("%d\n0 0\n", n);
        return 0;
    }

    for (int i = n-2; i >= 0; i--)
        acum[i] += acum[i+1];

    for (int i = n-2; i >= 0; i--)
        acum[i] = max(acum[i], acum[i+1]);

    int b = INF, e = INF, p = 1;
    ll aux = 0;
    for (int i = 0; i < n; i++) {
        p = max(p, i+1);

        ll rem = sum - aux - s;

        if (rem <= 0) {
            if (i < b+e) { b = i; e = 0; }
            continue;
        }

        while (p < n && acum[p] >= rem) p++;
        p--;

        if (p > i && acum[p] >= rem && i + n - p < b+e) {
            b = i; e = n-p;
        }
        aux += nums[i];
    }

    if (b+e == 2*INF) printf("-1\n");
    else printf("%d\n%d %d\n", n-b-e, b, e);

    return 0;
}
