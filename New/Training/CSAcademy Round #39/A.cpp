#include <bits/stdc++.h>

using namespace std;

int n, x;
bool app[100100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        app[x] = true;
    }

    int ans = 0;
    for (int i = 0; i < 100010; i++) {
        if (app[i]) ans++;
        if (app[i] && i % 2 == 1) app[i+1] = false;
    }
    printf("%d\n", ans);

    return 0;
}

