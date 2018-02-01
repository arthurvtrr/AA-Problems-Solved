#include <stdio.h>
#include <algorithm>

using namespace std;

#define EPS 1e-9

double func(double x) {
    //any convex function
}

int main() {
    //Ternary search for maximum value

    double left = 0.0, right = 100000.0;
    int iterations_left = 150;

    while (iterations_left--) {
        double leftThird = (2*left + right) / 3;
        double rightThird = (left + 2*right) / 3;

        if (func(leftThird) < func(rightThird) + EPS)
            left = leftThird;
        else
            right = rightThird;
    }

    return 0;
}
