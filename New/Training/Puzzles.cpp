#include <bits/stdc++.h>

using namespace std;

int n, m, pieces[55];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d", &pieces[i]);

    sort(pieces, pieces+m);
    int ans = 100000;
    for (int i = 0; i < m - n + 1; i++)
        ans = min(ans, pieces[i+n-1] - pieces[i]);

    printf("%d\n", ans);

    return 0;
}
