#include <bits/stdc++.h>

using namespace std;

int a, b, c, d;

int main() {
    scanf("%d %d %d %d", &a, &b, &c, &d);

    if (a > c) { swap(a, c); swap(b, d); }

    if (a == c) {
        int dist = abs(b - d);
        printf("%d %d %d %d\n", a+dist, b, c+dist, d);
    }
    else if (b == d) {
        int dist = abs(a - c);
        printf("%d %d %d %d\n", a, b+dist, c, d+dist);
    }
    else {
        if (abs(a - c) == abs(b - d)) printf("%d %d %d %d\n", a, d, c, b);
        else printf("-1\n");
    }

    return 0;
}
