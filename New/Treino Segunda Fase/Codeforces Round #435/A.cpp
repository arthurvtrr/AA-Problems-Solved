#include <bits/stdc++.h>

using namespace std;

int n, x, y, cont[110];

int main() {
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++) {
        scanf("%d", &y);
        cont[y] = 1;
    }

    int ans = 0;
    for (int i = 0; i < x; i++)
        if (cont[i] == 0)
            ans++;
    if (cont[x] == 1) ans++;
    printf("%d\n", ans);

    return 0;
}
