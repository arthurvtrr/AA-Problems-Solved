#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    int a, b, c, d;
    double min1, min2, max1, max2;
    while (scanf("%d %d %d %d", &a, &b, &c, &d), a, b, c, d) {
        if (a < b) {
            min1 = a; max1 = b;
        } else {
            min1 = b; max1 = a;
        }
        if (c < d) {
            min2 = c; max2 = d;
        } else {
            min2 = d; max2 = c;
        }
        double d1 = max2 / max1 * 100.0, d2 = min2 / min1 * 100.0;
        int sol = fmin(floor(d1), floor(d2));
        sol = fmin(100, sol);
        sol = fmax(sol, 1);
        printf("%d%\n", sol);
    }
    return 0;
}
