#include <stdio.h>
#include <algorithm>
#include <complex>

using namespace std;

#define PI acos(-1)

int n;

int rev(int k, int siz) {
    int sol = 0, log = log2(siz)-1;
    while (k) {
        if (k & 1)
            sol += 1 << log;
        k >>= 1;
        log--;
    }
    return sol;
}

void FFT(complex < long double > *coef, complex < long double > *pv, bool inverse) {
    int siz = 1 << ((int) ceil(log2(n+1)));
    siz *= 2;

    for (int k = 0; k < siz; k++)
        pv[rev(k, siz)] = coef[k];

    for (int s = 1; s <= log2(siz); s++) {
        int m = 1 << s;

        long double theta = (inverse? -1 : 1) * 2 * PI / m;
        complex < long double > unityRoot(cos(theta), sin(theta));

        for (int k = 0; k < siz; k += m) {
            complex < long double > omega = 1;

            for (int j = 0; j < m/2; j++) {
                complex < long double > t = omega * pv[k + j + m/2];
                complex < long double > u = pv[k + j];

                pv[k + j] = u + t;
                pv[k + j + m/2] = u - t;
                omega = omega * unityRoot;
            }
        }
    }

    if (inverse)
        for (int j = 0; j < siz; j++)
            pv[j] /= siz;
}
