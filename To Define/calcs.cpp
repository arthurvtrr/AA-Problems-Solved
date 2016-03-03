#include <stdio.h>

using namespace std;

int main() {
    int x1, q1, x2, q2;
    double v1, v2, t;

    scanf("%d %d %lf", &x1, &q1, &v1);
    scanf("%d %d %lf", &x1, &q2, &v2);

    t = q1 * v1 + q2 * v2;

    printf("VALOR A PAGAR: R$ %.2f\n", t);

    return 0;
}
