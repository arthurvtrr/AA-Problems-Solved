#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-13

int n;
struct people {
    double coord, speed;
} friends[60060];

double func(double x) {
    double ret = 0.0;
    for (int i = 0; i < n; i++)
        ret = max(ret, abs(x - friends[i].coord) / friends[i].speed);
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%lf", &friends[i].coord);
    for (int i = 0; i < n; i++)
        scanf("%lf", &friends[i].speed);

    double ini = 0.0, fim = 10000000000.0;
    int num_iter = 300;
    while (num_iter--) {
        double leftT = (2*ini + fim) / 3;
        double rightT = (ini + 2*fim) / 3;

        if (func(leftT) > func(rightT) + EPS) ini = leftT;
        else fim = rightT;
    }

    printf("%.12f\n", func(ini));
    return 0;
}

