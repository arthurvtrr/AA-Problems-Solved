#include <stdio.h>

using namespace std;

int main() {
    double A, B, MEDIA;

    scanf("%lf", &A);
    scanf("%lf", &B);

    MEDIA = (A*0.35 + B*0.75) * (10/11.0);

    printf("MEDIA = %.5f\n", MEDIA);

    return 0;
}
