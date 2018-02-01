#include <bits/stdc++.h>

using namespace std;

int m;
long long n;

int main() {
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lld", &n);
        printf("%lld\n", (n * (n - 1) / 2 + 1) * 2);
    }
    return 0;
}
