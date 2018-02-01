#include <bits/stdc++.h>

using namespace std;

int n;
long long p;

struct dev {
    long long power;
    long long stored;
} devs[100100];

int main() {
    scanf("%d %lld", &n, &p);

    for (int i = 0; i < n; i++)
        scanf("%lld %lld", &devs[i].power, &devs[i].stored);

    double ini = 0.000001, fim = 100000000000.0;
    int iter = 200;

    while (iter--) {
        double mid = (ini + fim) / 2;

        double sum = 0;
        for (int i = 0; i < n; i++) {
            double x = devs[i].stored, y = devs[i].power;

            double aux = (x / mid - y) / (-p);
            if (aux > 0.0) sum += aux;
        }
        if (sum <= 1.0) ini = mid;
        else fim = mid;
    }

    if (ini > 99999999999) printf("-1\n");
    else printf("%.9f\n", ini);

    return 0;
}
