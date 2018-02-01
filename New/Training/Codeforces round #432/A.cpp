#include <bits/stdc++.h>

using namespace std;

int n, t, k;

int main() {
    scanf("%d %d %d", &n, &k, &t);
    if (t < k) printf("%d\n", t);
    else if (t <= n) printf("%d\n", k);
    else printf("%d\n", k - (t - n));

    return 0;
}
