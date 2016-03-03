#include <stdio.h>
#include <algorithm>

using namespace std;

long long freq[110000], dp[110000];

int main() {
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        freq[x]++;
    }

    dp[1] = freq[1];
    for (int i = 2; i <= 100100; i++)
        dp[i] = max(dp[i-1], dp[i-2] + freq[i] * i);

    printf("%lld\n", dp[100100]);
    return 0;
}
