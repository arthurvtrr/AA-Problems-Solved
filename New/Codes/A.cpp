#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int n1, n2, as[14], bs[14];
long double r1, r2;
long double const EPS = 1e-100;

#define ll long long

void convert(long double x) {
    vector < ll > quotients;

    quotients.push_back((ll) (x + EPS));

    if (fabs(quotients[0]*1.0 - x) > EPS) {
        bool finished = false;

        for (int i = 0; i < 80; i++) {
            quotients.push_back(0);

            int iterLeft = 200;
            ll ini = 1, fim = 10000000000000000LL;
            while (iterLeft--) {
                ll mid = (ini + fim) / 2;

                quotients[i+1] = mid;

                long double aux = 0.0;
                for (int k = i+1; k >= 0; k--) {
                    if (k != i+1) aux = 1.0/aux;
                    aux = quotients[k] + (quotients[k] < 0? -1 : 1) * aux;
                }

                if (fabs(aux - x) < EPS) {
                    finished = true;
                    break;
                }
                else if (i % 2 == 0 && aux < x - EPS)
                    fim = mid;
                else if (i % 2 != 0 && x < aux - EPS)
                    fim = mid;
                else ini = mid;
            }

            if (finished) break;
        }
    }

    for (int i = 0; i < (int) quotients.size(); i++) {
        if (i > 0) printf(" ");
        printf("%lld", quotients[i]);
    }
    printf("\n");
}

int main() {
    int cont = 1;
    while (1) {
        scanf("%d %d", &n1, &n2);
        if (n1 + n2 == 0) break;

        r1 = 0.0, r2 = 0.0;
        for (int i = 0; i < n1; i++)
            scanf("%d", &as[i]);
        for (int i = 0; i < n2; i++)
            scanf("%d", &bs[i]);

        for (int i = n1-1; i >= 0; i--) {
            if (i != n1-1) r1 = 1.0/r1;
            r1 = as[i] + (as[i] < 0? -1 : 1) * r1;
        }
        for (int i = n2-1; i >= 0; i--) {
            if (i != n2-1) r2 = 1.0/r2;
            r2 = bs[i] + (bs[i] < 0? -1 : 1) * r2;
        }

        printf("Case %d:\n", cont++);

        long double sum = r1 + r2, sub = r1 - r2, mult = r1 * r2, div = r1 / r2;

        printf("%.100Lf %.100Lf %.100Lf %.100Lf\n", sum, sub, mult, div);
        convert(sum);
        convert(sub);
        convert(mult);
        convert(div);
    }
    return 0;
}
