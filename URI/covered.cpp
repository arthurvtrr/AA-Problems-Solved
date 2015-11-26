#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    int v1, v2, t, d;

    scanf("%d %d", &v1, &v2);
    scanf("%d %d", &t, &d);

    int s = v1 + v2, last = v1;

    for (int i = 1; i < t-1; i++) {
        last = fmin(last + d, (t - 1 - i) * d + v2);
        s += last;
    }

    printf("%d\n", s);

    return 0;
}
