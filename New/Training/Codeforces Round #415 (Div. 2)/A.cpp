#include <bits/stdc++.h>

using namespace std;

int n, k, marks[110];

int main() {
    scanf("%d %d", &n, &k);
    double sum = 0.0;
    int ans = 0, quant = n;

    for (int i = 0; i < n; i++) {
        scanf("%d", &marks[i]);
        sum += marks[i];
    }

    while (round(sum / quant) < k) {
        sum += k;
        quant++;
        ans++;
    }

    printf("%d\n", ans);

    return 0;
}
