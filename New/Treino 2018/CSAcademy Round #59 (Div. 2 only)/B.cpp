#include <bits/stdc++.h>

using namespace std;

int g1, p1, g2, p2;

int main() {
    scanf("%d %d %d %d", &g1, &p1, &g2, &p2);

    int a, b;
    for (int i = 0; i <= g1; i++) {
        if (i * 100 / g1 == p1) {
            a = i;
            break;
        }
    }
    for (int i = g2; i >= 0; i--) {
        if (i * 100 / g2 == p2) {
            b = i;
            break;
        }
    }

    printf("%d\n", min(g2 - g1, b - a));

    return 0;
}
