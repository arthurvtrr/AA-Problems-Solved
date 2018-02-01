#include <bits/stdc++.h>

using namespace std;

#define MAX 500500

int n, m, nums[50050], x, y, mob[MAX], simple[MAX];
vector < int > divs[MAX];

void mobius() {
    for (int i = 2; i < MAX; i++)
        if (simple[i] == 1)
            for (int j = i; j < MAX; j += i) {
                mob[j] *= -1;
                simple[j] *= i;
                if ((j / i) % i == 0) mob[j] = 0;
            }
}

int cnt[MAX], nxtCoprime[50050];

int main() {
    for (int i = 0; i < MAX; i++)
        mob[i] = simple[i] = 1;
    mobius();

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        nums[i] = simple[nums[i]];
    }

    for (int i = 1; i < MAX; i++)
        for (int j = i; j < MAX; j += i)
            if (mob[j])
                divs[j].push_back(i);

    int r = 0, total = 0;
    for (int i = 0; i < n; i++) {
        while (r < n && total == 0) {
            for (int div : divs[nums[r]]) {
                total += mob[div] * cnt[div];
                cnt[div]++;
            }
            r++;
        }

        nxtCoprime[i] = r - (total != 0);

        for (int div : divs[nums[i]]) {
            cnt[div]--;
            total -= mob[div] * cnt[div];
        }
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        if (nxtCoprime[x-1] <= y-1) printf("S\n");
        else printf("N\n");
    }

    return 0;
}
