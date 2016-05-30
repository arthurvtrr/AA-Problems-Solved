#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <complex>

using namespace std;

#define PI acos(-1)
#define MAX_N 150000
#define STEP 5

int t, n;
complex < long double > polin1[MAX_N], polin2[MAX_N], aux1[MAX_N], aux2[MAX_N], result[MAX_N];
long long sol[MAX_N];

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
    int siz = 1 << ((int) ceil(log2(n)));
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

int main() {
    scanf("%d", &t);

    while (t--) {
        for (int i = 0; i < MAX_N; i++)
            polin1[i] = polin2[i] = aux1[i] = aux2[i] = result[i] = 0;

        string a, b;
        cin >> a >> b;

        int a_siz = ceil(1.0 * a.size() / STEP), b_siz = ceil(1.0 * b.size() / STEP);
        n = max(a_siz, b_siz);

        int pos = a_siz;
        for (int i = a.size()-1; i >= 0; i -= STEP) {
            int aux = 0;
            for (int j = max(i-STEP+1, 0); j <= i; j++) {
                aux *= 10;
                aux += a[j] - '0';
            }
            polin1[--pos] = {aux, 0};
        }

        pos = b_siz;
        for (int i = b.size()-1; i >= 0; i -= STEP) {
            int aux = 0;
            for (int j = max(i-STEP+1, 0); j <= i; j++) {
                aux *= 10;
                aux += b[j] - '0';
            }
            polin2[--pos] = {aux, 0};
        }

        FFT(polin1, aux1, false);
        FFT(polin2, aux2, false);

        for (int i = 0; i < MAX_N; i++)
            aux1[i] *= aux2[i];

        FFT(aux1, result, true);

        for (int i = 0; i < a_siz + b_siz - 1; i++)
            sol[i] = (long long) round(result[i].real());

        int max_c = pow(10, STEP);
        for (int i = MAX_N; i > 0; i--)
            if (sol[i] > max_c - 1) {
                sol[i-1] += sol[i] / max_c;
                sol[i] %= max_c;
            }

        for (int i = 0; i < a_siz + b_siz - 1; i++) {
            if (i == 0 && sol[i] == 0) {
                printf("0");
                break;
            }
            if (i != 0) {
                long long siz = 0, aux = sol[i];
                while (aux) {
                    siz++;
                    aux /= 10;
                }
                for (int j = 0; j < STEP-siz; j++)
                    printf("0");
            }

            if (sol[i] != 0) printf("%lld", sol[i]);
        }
        printf("\n");
    }

    return 0;
}
