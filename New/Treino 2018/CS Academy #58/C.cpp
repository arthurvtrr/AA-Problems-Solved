#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, m, a, b;
set < pii > aux;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        if (a > b) swap(a, b);
        aux.insert(pii(a, b));
    }

    int ans = 1;

    for (int i = 1; i < n-1; i++) {
        int siz = 1, x = i-1, y = i+1;
        while (x >= 0 && y < n && aux.count(pii(x, y))) {
            siz += 2;
            x--; y++;
        }
        ans = max(ans, siz);
    }

    for (int i = 0; i < n-1; i++) {
        int siz = 0, x = i, y = i+1;
        while (x >= 0 && y < n && aux.count(pii(x, y))) {
            siz += 2;
            x--; y++;
        }
        ans = max(ans, siz);
    }

    printf("%d\n", ans);

    return 0;
}
