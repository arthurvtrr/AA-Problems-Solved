#include <bits/stdc++.h>

using namespace std;

int n, a[100100], b[100100];

int main() {
    scanf("%d", &n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    sort(b, b+n);

    if (sum <= b[n-1] + b[n-2]) printf("YES\n");
    else printf("NO\n");

    return 0;
}
