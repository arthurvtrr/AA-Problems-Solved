#include <bits/stdc++.h>

using namespace std;

int n, nums[110];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            for (int k = j+1; k < n; k++) {
                vector < int > vals = {nums[i], nums[j], nums[k]};
                sort(vals.begin(), vals.end());
                if (vals[2] < vals[1] + vals[0])
                    ans++;
            }
    printf("%d\n", ans);

    return 0;
}
