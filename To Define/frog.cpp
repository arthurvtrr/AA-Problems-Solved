#include <bits/stdc++.h>

using namespace std;

int main() {
    long long m, h1, a1, h2, a2, x1, y1, x2, y2;
    scanf("%I64d", &m);
    scanf("%I64d %I64d", &h1, &a1);
    scanf("%I64d %I64d", &x1, &y1);
    scanf("%I64d %I64d", &h2, &a2);
    scanf("%I64d %I64d", &x2, &y2);

    int sec = 0;
    bool f = false;

    for (int i = 0; i < 30000000; i++) {
        h1 = (x1 * h1 + y1) % m;
        h2 = (x2 * h2 + y2) % m;
        sec++;
        if (h1 == a1 && h2 == a2) {
            f = true;
            break;
        }
    }

    if (!f) printf("-1\n");
    else printf("%d\n", sec);

    return 0;
}
