#include <bits/stdc++.h>

using namespace std;

int main() {
    int k, n, w, total;
    scanf("%d %d %d", &k, &n, &w);

    total = w * (k + w*k) / 2;

    if (total <= n) printf("0\n");
    else printf("%d\n", total - n);

    return 0;
}
