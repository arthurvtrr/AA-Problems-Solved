#include <stdio.h>

using namespace std;

int main() {
    double x, y;

    scanf("%lf %lf", &x, &y);

    if (y == 0 && x == 0)
        printf("Origem\n");
    else if (y == 0 && x != 0)
        printf("Eixo X\n");
    else if (y != 0 && x == 0)
        printf("Eixo Y\n");
    else if (y > 0 && x > 0)
        printf("Q1\n");
    else if (y > 0 && x < 0)
        printf("Q2\n");
    else if (y < 0 && x < 0)
        printf("Q3\n");
    else
        printf("Q4\n");

    return 0;
}
