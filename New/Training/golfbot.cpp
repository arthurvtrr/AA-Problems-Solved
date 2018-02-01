#include <stdio.h>
#include <algorithm>
#include <complex>
#include <math.h>

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

int a, b, nums[200200], holes[200200];
bool possible[660000];
complex < long double > coefs1[660000], coefs2[660000], inv1[660000], inv2[660000], ult[660000];

int main() {
    while (scanf("%d", &a) != EOF) {
        for (int i = 0; i < 660000; i++) {
            possible[i] = false;
            coefs1[i] = coefs2[i] = inv1[i] = inv2[i] = ult[i] = {0, 0};
        }

        int maxi = 0;

        for (int i = 0; i < a; i++) {
            scanf("%d", &nums[i]);
            possible[nums[i]] = true;
            coefs1[nums[i]] = coefs2[nums[i]] = {1, 0};

            if (nums[i] > maxi) maxi = nums[i];
        }

        n = maxi+1;

        scanf("%d", &b);

        for (int i = 0; i < b; i++)
            scanf("%d", &holes[i]);

        FFT(coefs1, inv1, false);
        FFT(coefs2, inv2, false);

        for (int i = 0; i < 600600; i++)
            inv1[i] *= inv2[i];

        FFT(inv1, ult, true);

        for (int i = 0; i < 600600; i++)
            if (ult[i].real() > 0.5)
                possible[i] = true;

        int sol = 0;
        for (int i = 0; i < b; i++)
            if (possible[holes[i]])
                sol++;

        printf("%d\n", sol);
    }

    return 0;
}
