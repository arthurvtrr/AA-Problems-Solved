#include <stdio.h>

using namespace std;

int main() {
    int n, k, p, q;
    scanf("%d", &n);
    for (int t = 0; t < n; t++) {
        scanf("%d %d/%d", &k, &p, &q);
        int den = q * (2 * (p / q)) - p + q;
        printf("%d %d/%d\n", k, q, den);
    }
    return 0;
}
