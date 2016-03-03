#include <stdio.h>

using namespace std;

int buscaBinaria(int x, int n, int v[]) {
    int e = 0, m, d = n - 1;
    while (e <= d) {
        m = (e + d) / 2;
        if (v[m] == x) return m;
        if (v[m] < x) e = m + 1;
        else d = m - 1;
    }
    return -1;
}

int main() {
    int a, b;

    while (1) {
        scanf("%d %d", &a, &b);
        if (a == 0 && b == 0) break;

        int t, x[11000], y[11000], d1 = 0, d2 = 0;

        for (int i = 1; i <= a; i++)
            scanf("%d", &x[i]);

        for (int i = 1; i <= b; i++) {
            scanf("%d", &y[i]);
            if (buscaBinaria(y[i], a+1, x) == -1 && y[i] != y[i-1])
                d2++;
        }

        for (int i = 1; i <= a; i++) {
            if (buscaBinaria(x[i], b+1, y) == -1 && x[i] != x[i-1])
                d1++;
        }

        printf("%d\n", d1 < d2? d1 : d2);
    }

    return 0;
}
