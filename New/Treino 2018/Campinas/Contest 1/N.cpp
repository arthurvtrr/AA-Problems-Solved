#include <bits/stdc++.h>

using namespace std;

int n, a, nums[10010], lst[10010];

int main() {
    scanf("%d %d", &n, &a);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    int s = nums[0];
    for (int i = 1; i < n; i++)
        s += abs(nums[i]);

    memset(lst, -1, sizeof lst);
    lst[0] = 0;

    int x;
    for (int i = 1; i < n; i++) {
        x = abs(nums[i]);
        if (x == 0) continue;

        for (int j = 10000; j >= 0; j--)
            if (lst[j] != -1 && x+j <= 10000 && lst[x+j] == -1)
                lst[x+j] = i;
    }

    int best = 0;
    for (int i = 1; i < 10010; i++)
        if (lst[i] != -1 && abs(a - (s - 2*i)) < abs(a - (s - 2*best)))
            best = i;

    printf("%d\n", s - 2*best);

    set < int > neg;
    while (best != 0) {
        neg.insert(lst[best]);
        best -= abs(nums[lst[best]]);
    }

    printf("%d", nums[0]);
    for (int i = 1; i < n; i++) {
        if (neg.count(i)) {
            if (nums[i] < 0) printf("+%d", nums[i]);
            else printf("-%d", nums[i]);
        }
        else {
            if (nums[i] < 0) printf("-%d", nums[i]);
            else printf("+%d", nums[i]);
        }
    }
    printf("\n");

    return 0;
}
