#include <stdio.h>

using namespace std;

int main() {
    double A, B, C, MEDIA;

    scanf("%lf", &A);
    scanf("%lf", &B);
    scanf("%lf", &C);

    MEDIA = A*0.2 + B*0.3 + C*0.5;

    printf("MEDIA = %.1f\n", MEDIA);

    return 0;
}
