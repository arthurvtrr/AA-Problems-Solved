#include <bits/stdc++.h>

using namespace std;

int n, nums[100100];
bool valid[200100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    for (int i = n-1; i >= 0; i--)
        if (i + nums[i] == n - 1 || valid[i + nums[i] + 1])
            valid[i] = true;

    for (int i = 0; i <= n; i++)
        if (valid[i] || i == n)
            printf("%d\n", i);

    return 0;
}

