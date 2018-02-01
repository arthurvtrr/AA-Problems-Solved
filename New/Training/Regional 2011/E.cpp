#include <bits/stdc++.h>

using namespace std;

int l, c, r1, r2;

int main() {
    while (1) {
        scanf("%d %d %d %d", &l, &c, &r1, &r2);
        if (l + c + r1 + r2 == 0) break;

        bool possible = false;

        int ax = r1, ay = r1, bx = l - r2, by = c - r2;
        if (min(l, c) >= max(2*r1, 2*r2) && (ax - bx)*(ax - bx) + (ay - by)*(ay - by) >= (r1 + r2)*(r1 + r2)) possible = true;

        if (possible) printf("S\n");
        else printf("N\n");
    }
    return 0;
}
