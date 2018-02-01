#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t, n, m, mins[1010], offer[1010], jobs[1010], atual[1010];
char qual[1010][1010];

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(atual, 0, sizeof atual);

        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &mins[i]);
        for (int i = 0; i < m; i++)
            scanf("%d %d", &offer[i], &jobs[i]);
        for (int i = 0; i < n; i++)
            scanf("%s", qual[i]);

        ll numC = 0, tots = 0, comp = 0;
        for (int i = 0; i < n; i++) {
            int best = -1;
            for (int j = 0; j < m; j++)
                if (qual[i][j] == '1' && atual[j] < jobs[j] && offer[j] >= mins[i]) {
                    if (best == -1) best = j;
                    else if (offer[j] > offer[best]) best = j;
                }
            if (best > -1) {
                numC++;
                tots += offer[best];
                atual[best]++;
            }
        }

        for (int i = 0; i < m; i++)
            if (atual[i] == 0)
                comp++;

        printf("%lld %lld %lld\n", numC, tots, comp);
    }

    return 0;
}
