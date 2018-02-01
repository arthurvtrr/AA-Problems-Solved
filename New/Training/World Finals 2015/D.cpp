#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9
#define PI acos(-1)

int n, s;

struct sphere {
    long double r, x, y, z;
} sps[10010];

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n; i++)
        scanf("%Lf %Lf %Lf %Lf", &sps[i].r, &sps[i].x, &sps[i].y, &sps[i].z);

    long double need = 10000000000.0;
    need *= 100000.0;
    for (int i = 0; i < n; i++)
        need -= 4 / 3.0 * PI * sps[i].r * sps[i].r * sps[i].r;
    need /= s;

    long double atual = 0.0;

    for (int i = 0; i < s; i++) {
        long double ini = atual, fim = 100000.0;

        while (fabs(ini - fim) > EPS) {
            long double mid = (ini + fim) / 2;
            long double total = fabs(mid - atual) * 10000000000.0;

            for (int j = 0; j < n; j++)
                if (sps[j].z - sps[j].r >= atual && sps[j].z + sps[j].r <= mid) {
                    total -= 4 / 3.0 * PI * sps[j].r * sps[j].r * sps[j].r;
                }
                else if (sps[j].z - sps[j].r >= atual && sps[j].z - sps[j].r <= mid) {
                    long double h = fabs(mid - (sps[j].z - sps[j].r));
                    long double c = sqrtl(h * (2*sps[j].r - h));
                    total -= PI / 6 * h * (3*c*c + h*h);
                }
                else if (sps[j].z + sps[j].r >= atual && sps[j].z + sps[j].r <= mid) {
                    long double h = fabs(sps[j].z + sps[j].r - atual);
                    long double c = sqrtl(h * (2*sps[j].r - h));
                    total -= PI / 6 * h * (3*c*c + h*h);
                }
                else if (sps[j].z - sps[j].r <= atual && sps[j].z + sps[j].r >= mid) {
                    long double h = fabs(sps[j].z + sps[j].r - atual);
                    long double c = sqrtl(h * (2*sps[j].r - h));
                    total -= PI / 6 * h * (3*c*c + h*h);
                    h = fabs(sps[j].z + sps[j].r - mid);
                    c = sqrtl(h * (2*sps[j].r - h));
                    total += PI / 6 * h * (3*c*c + h*h);
                }

            if (total < need) ini = mid;
            else fim = mid;
        }
        printf("%.10Lf\n", fabs(fim - atual) / 1000.0);
        atual = fim;
    }

    return 0;
}

