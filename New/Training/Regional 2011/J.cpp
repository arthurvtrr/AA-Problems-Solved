#include <bits/stdc++.h>

using namespace std;

int n, x, ans;

int main() {
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int p = 0; p < n; p++) {
            ans = -1;
            for (int i = 0; i < 5; i++) {
                scanf("%d", &x);
                if (x <= 127 && ans == -1) ans = i;
                else if (x <= 127 && ans >= 0) ans = -2;
            }

            if (ans < 0) printf("*\n");
            else printf("%c\n", ans + 'A');
        }
    }
    return 0;
}
