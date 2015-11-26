#include <stdio.h>

using namespace std;

struct card {
    int a;
    int d;
    int h;
} cards[22];

int main() {
    int n, a, d, h;
    scanf("%d %d %d %d", &n, &a, &d, &h);
    int mask = 1 << n;
    for (int i = 0; i < n; i++)
        scanf("%d %d %d", &cards[i].a, &cards[i].d, &cards[i].h);

    bool p = false;

    for (int i = 0; i < mask; i++) {
        int s1 = 0, s2 = 0, s3 = 0, tmp = i, c = 0, u = 0;

        while (tmp) {
            if (tmp & 1) {
                s1 += cards[c].a;
                s2 += cards[c].d;
                s3 += cards[c].h;
                u++;
            }
            tmp >>= 1;
            c++;
        }

        if (s1 == a && s2 == d && s3 == h && u > 1) p = true;
    }

    if (p) printf("Y\n");
    else printf("N\n");
    return 0;
}
