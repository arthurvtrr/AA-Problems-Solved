#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int main() {
    double x, y;
    while (scanf("%lf %lf", &x, &y) != EOF) {
        int sol = ceil(1 / (1 - x / y));
        printf("%d\n", sol);
    }
}
