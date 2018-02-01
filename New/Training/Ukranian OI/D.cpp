#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define ull unsigned long long

ull a, b, x, y;

int main() {
    scanf("%llu %llu", &a, &b);

    ull pos = 63;

    while (1) {
        if (pos == 0) break;
        else pos--;

        if (b & (1LL << pos)) {
            y += 1LL << pos;
        }
        else if (2 * (1LL << pos) + x + y <= a) {
            y += 1LL << pos;
            x += 1LL << pos;
        }
    }

    if (x + y != a) printf("-1\n");
    else printf("%llu %llu\n", x, y);

    return 0;
}
