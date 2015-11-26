#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    double x, n;
    int i = 1;
    while (1) {
        scanf("%lf", &x);
        if (x == 0) break;

        n = ceil((3 + sqrt(9 + 8 * x)) / 2);

        printf("Case %d: %.0lf\n", i++, n);
    }
    return 0;
}
