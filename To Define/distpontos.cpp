#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    double x1, y1, x2, y2, dist;

    scanf("%lf %lf", &x1, &y1);
    scanf("%lf %lf", &x2, &y2);

    dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));

    printf("%.4f\n", dist);

    return 0;
}
