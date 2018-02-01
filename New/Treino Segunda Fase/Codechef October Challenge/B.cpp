#include <bits/stdc++.h>

using namespace std;

int t, n, k, x;
bool app[300300];

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(app, 0, sizeof app);

        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            app[x] = true;
        }

        int ans = 0;
        for (int i = 0; i < 300300; i++) {
            if (app[i]) continue;
            else if (k) { k--; continue; }
            ans = i; break;
        }
        printf("%d\n", ans);
    }
    return 0;
}
