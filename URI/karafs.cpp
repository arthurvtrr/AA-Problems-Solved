#include <stdio.h>

using namespace std;

int main() {
    int a, b, n, l, t, m;

    scanf("%d %d %d", &a, &b, &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &l, &t, &m);

        int indx = (t - a) / b + 1;
        int ar = a + (indx - 1) * b;
        int arl1 = a + (l - 1) * b;
        int st = ((a + ar) * indx) / 2;
        int stl1 = ((a + arl1) * indx) / 2, stf1 = st - stl1;

        bool f = false;

        if (indx >= l && ar <= t && stf1 <= t * m) {
            printf("%d\n", indx);
            continue;
        }

        if (indx >= l) {
            indx--;
            while (indx >= l) {
                int ar1 = a + (indx - 1) * b;
                int arl = a + (l - 1) * b;
                int st1 = ((a + ar1) * indx) / 2;
                int stl = ((a + arl) * indx) / 2;
                int stf = st1 - stl;

                if (ar1 <= t && stf <= t * m) {
                    printf("%d\n", indx);
                    f = true;
                    break;
                }
                indx--;
            }
        }
        if (!f) printf("-1\n");

    }
    return 0;
}
