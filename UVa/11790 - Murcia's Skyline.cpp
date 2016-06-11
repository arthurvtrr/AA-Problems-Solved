#include <stdio.h>
#include <algorithm>

using namespace std;

int t, n, heights[11000], lens[11000], inc[11000], dec[11000];

int main() {
    scanf("%d", &t);

    for (int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &heights[i]);
        for (int i = 0; i < n; i++)
            scanf("%d", &lens[i]);

        for (int i = 0; i < n; i++) {
            inc[i] = lens[i];
            dec[i] = lens[i];
            for (int j = i-1; j >= 0; j--) {
                if (heights[i] > heights[j]) inc[i] = max(inc[i], lens[i] + inc[j]);
                if (heights[i] < heights[j]) dec[i] = max(dec[i], lens[i] + dec[j]);
            }
        }

        int inc_len = 0, dec_len = 0;

        for (int i = 0; i < n; i++) {
            inc_len = max(inc_len, inc[i]);
            dec_len = max(dec_len, dec[i]);
        }

        if (inc_len >= dec_len) printf("Case %d. Increasing (%d). Decreasing (%d).\n", tc, inc_len, dec_len);
        else printf("Case %d. Decreasing (%d). Increasing (%d).\n", tc, dec_len, inc_len);
    }
    return 0;
}
