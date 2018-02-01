#include <bits/stdc++.h>

using namespace std;

int n, s;

struct sugar {
    int x, y;
} sugars[110];

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &sugars[i].x, &sugars[i].y);

    int ans = -1;
    for (int i = 0; i < n; i++) {
        if (sugars[i].x < s && sugars[i].y > 0)
            ans = max(ans, 100 - sugars[i].y);
        else if (sugars[i].x <= s && sugars[i].y == 0)
            ans = max(ans, 0);
    }

    printf("%d\n", ans);

    return 0;
}
