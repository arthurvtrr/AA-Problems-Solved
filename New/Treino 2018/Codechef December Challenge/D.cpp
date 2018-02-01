#include <bits/stdc++.h>

using namespace std;

#define SIZ 320

int n, q, nums[100100], orig[100100], t, x, y, acum[SIZ];
unordered_map < int, int > quant[SIZ];

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        orig[i] = nums[i];
        if (i) nums[i] ^= nums[i-1];
        quant[i / SIZ][nums[i]]++;
    }

    for (int j = 0; j < q; j++) {
        scanf("%d %d %d", &t, &x, &y);
        x--;
        if (t == 1) {
            int aux = orig[x];
            orig[x] = y;
            for (int i = x; i < min(x/SIZ*SIZ + SIZ, n); i++) {
                quant[x/SIZ][nums[i]^aux^y]++;
                quant[x/SIZ][nums[i]]--;
                nums[i] ^= aux ^ y;
            }
            for (int i = x/SIZ+1; i < SIZ; i++)
                acum[i] ^= aux ^ y;
        }
        else {
            int ans = 0;
            for (int i = 0; i < x/SIZ; i++)
                if (quant[i].count(y ^ acum[i]))
                    ans += quant[i][y ^ acum[i]];
            for (int i = x/SIZ*SIZ; i <= x; i++)
                if ((nums[i] ^ acum[x/SIZ]) == y)
                    ans++;
            printf("%d\n", ans);
        }
    }
    return 0;
}
