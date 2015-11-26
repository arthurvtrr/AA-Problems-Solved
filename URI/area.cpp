#include <stdio.h>

using namespace std;

#define PI 3.14159
int main() {
    double r, a;

    scanf("%lf", &r);

    a = PI * (r*r);

    printf("A=%.4f\n", a);

    return 0;
}
