#include <bits/stdc++.h>

using namespace std;

int n;
long long nums[100100], aux1[100100], aux2[100100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &nums[i]);

    for (int i = 0; i < n-1; i++) {
        aux1[i] = abs(nums[i] - nums[i+1]) * (i % 2 == 0? -1 : 1);
        aux2[i] = abs(nums[i] - nums[i+1]) * (i % 2 != 0? -1 : 1);
    }

    long long ans = 0;

    long long maxi = 0, atual = 0;
    for (int i = 0; i < n-1; i++) {
        atual += aux1[i];
        maxi = max(atual, maxi);
        if (atual < 0) atual = 0;
    }
    ans = max(ans, maxi);

    maxi = 0, atual = 0;
    for (int i = 0; i < n-1; i++) {
        atual += aux2[i];
        maxi = max(atual, maxi);
        if (atual < 0) atual = 0;
    }
    ans = max(ans, maxi);

    printf("%lld\n", ans);

    return 0;
}
