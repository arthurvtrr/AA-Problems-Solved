#include <bits/stdc++.h>

using namespace std;

long long n, k;

int main() {
    scanf("%lld %lld", &n, &k);
    if ((n / k) % 2LL) printf("YES\n");
    else printf("NO\n");

    return 0;
}

