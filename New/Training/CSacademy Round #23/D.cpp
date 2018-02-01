#include <bits/stdc++.h>

using namespace std;

int n;
long long pos[100100], minr[100100], maxr[100100];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lld", &pos[i]);
    for (int i = 0; i < n; i++)
        scanf("%lld %lld", &minr[i], &maxr[i]);

    long long x = minr[0], y = maxr[0], acum = 0, a = y, b = x;
    for (int i = 1; i < n; i++) {
        if (minr[i] > pos[i] - pos[i-1] - acum - a) {
            if (i % 2 == 1) y -= minr[i] - (pos[i] - pos[i-1] - acum - a);
            else x += minr[i] - (pos[i] - pos[i-1] - acum - a);
        }
        if (maxr[i] < pos[i] - pos[i-1] - acum - b) {
            if (i % 2 == 1) x += pos[i] - pos[i-1] - acum - b - maxr[i];
            else y -= pos[i] - pos[i-1] - acum - b - maxr[i];
        }

        acum = pos[i] - pos[i-1] - acum;

        if (i % 2 == 1) { a = -x; b = -y; }
        else { a = y; b = x; }
    }

    printf("%lld\n", max(0LL, y - x + 1));

    return 0;
}

