#include <bits/stdc++.h>

using namespace std;

int n, t, nums[200200];
map < int, int > aux;

int main() {
    scanf("%d %d", &n, &t);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        if (max(0, nums[i] - i) < t - i) {
            aux[max(0, nums[i] - i)]++;
            aux[t - i]--;
        }
    }

    int ans = 0, sum = 0;
    for (auto v : aux) {
        sum += v.second;
        ans = max(ans, sum);
    }
    printf("%d\n", ans);

    return 0;
}
