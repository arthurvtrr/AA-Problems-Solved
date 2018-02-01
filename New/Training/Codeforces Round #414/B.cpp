#include <bits/stdc++.h>

using namespace std;

int n, h;

int main() {
    scanf("%d %d", &n, &h);
    double A = 1.0 * h / 2 / n, aux = 1.0 * h / 2 / n;

    for (int i = 0; i < n-1; i++) {
        double ini = 0.0, fim = h;
        int iter = 200;

        while (iter--) {
            double mid = (ini + fim) / 2;
            if (mid*mid / 2 / h <= A) ini = mid;
            else fim = mid;
        }

        if (i) printf(" ");
        printf("%.12f", ini);
        A += aux;
    }
    printf("\n");

    return 0;
}

