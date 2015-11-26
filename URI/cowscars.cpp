#include <stdio.h>

using namespace std;

int main() {
    double ncows, ncars, nshow;

    while (scanf("%lf %lf %lf", &ncows, &ncars, &nshow) != EOF) {
        double t = ncows + ncars, r = t - nshow - 1;

        double x = (ncows / t) * (ncars / r) + (ncars / t) * ((ncars - 1) / r);

        printf("%.5lf\n", x);
    }

    return 0;
}
