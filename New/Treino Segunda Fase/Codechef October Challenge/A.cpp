#include <bits/stdc++.h>

using namespace std;

int t, n, p, nums[550];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &p);
        int cnt[2] = {0, 0};
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
            if (nums[i] >= p / 2) cnt[0]++;
            else if (nums[i] <= p / 10) cnt[1]++;
        }
        if (cnt[0] == 1 && cnt[1] == 2) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}
