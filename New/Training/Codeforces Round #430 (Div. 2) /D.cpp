#include <bits/stdc++.h>

using namespace std;

int n, m, x, ans[600600];
bool app[600600];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        app[x] = true;
    }

    memset(ans, -1, sizeof ans);

    int acum = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &x);
        acum ^= x;

        if (ans[acum] != -1) printf("%d\n", ans[acum]);
        else {
            for (int j = 0; j < 300300; j++)
                if (!app[acum ^ j]) {
                    ans[acum] = j;
                    printf("%d\n", j);
                    break;
                }
        }
    }

    return 0;
}

