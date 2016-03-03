#include <stdio.h>
#include <math.h>

using namespace std;

int l, c, r1, r2;

int main() {
    while(1) {
        scanf("%d %d %d %d", &l, &c, &r1, &r2);

        if (l == 0 && c == 0 && r1 == 0 && r2 == 0) break;

        int x1 = r1, y1 = r1, x2 = l - r2, y2 = c - r2, dm1 = r1 * 2, dm2 = r2 * 2;

        if (fmax(dm1, dm2) > fmin(l,c))
            printf("N\n");
        else if (sqrt(pow(x2-x1, 2) + pow(y2-y1, 2)) >= r1 + r2)
            printf("S\n");
        else
            printf("N\n");
    }
    return 0;
}
