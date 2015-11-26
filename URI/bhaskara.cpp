#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int main() {
    double a, b, c, r1, r2, d;

    scanf("%lf %lf %lf", &a, &b, &c);

    d = b*b - 4*a*c;

    if (a == 0 || d < 0) {
        printf("Impossivel calcular\n");
        exit(0);
    }

    r1 = (-b + sqrt(d)) / (2*a);
    r2 = (-b - sqrt(d)) / (2*a);

    printf("R1 = %.5f\n", r1);
    printf("R2 = %.5f\n", r2);

    return 0;
}
