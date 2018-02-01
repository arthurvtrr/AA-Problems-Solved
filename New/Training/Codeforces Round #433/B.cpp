#include <bits/stdc++.h>

using namespace std;

int n, k;

int main() {
    scanf("%d %d", &n, &k);
    if (k == 0 || k == n) printf("0 0\n");
    else printf("1 %d\n", min(k * 2, n - k));

    return 0;
}
