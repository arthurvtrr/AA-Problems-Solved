#include <bits/stdc++.h>

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

complex < double > aux[8400000];

void FFT(complex < double > *coef, bool inverse) {
	int siz = 1 << ((int) ceil(log2(n+1)));
	siz *= 2;

	for (int i = 0; i < siz; i++)
		aux[i] = coef[i];

	for (int k = 0; k < siz; k++)
		coef[rev(k, siz)] = aux[k];

	for (int s = 1; s <= log2(siz); s++) {
		int m = 1 << s;

		double theta = (inverse? -1 : 1) * 2 * PI / m;
		complex < double > unityRoot(cos(theta), sin(theta));

		for (int k = 0; k < siz; k += m) {
			complex < double > omega = 1;

			for (int j = 0; j < m/2; j++) {
				complex < double > t = omega * coef[k + j + m/2];
				complex < double > u = coef[k + j];

				coef[k + j] = u + t;
				coef[k + j + m/2] = u - t;
				omega = omega * unityRoot;
			}
		}
	}

	if (inverse)
		for (int j = 0; j < siz; j++)
			coef[j] /= siz;
}

string s;
int acum[3000300];
complex < double > coefs1[8400000], coefs2[8400000];

int main() {
	cin >> s;
	n = 26 * s.size() + 2;

    for (int i = 0; i < s.size(); i++) {
        acum[i+1] = (s[i] - 'a') + 1;
        acum[i+1] += acum[i];
    }

	for (int i = 0; i <= s.size(); i++) {
        coefs1[acum[i]] = {1, 0};
        coefs2[acum[s.size()] - acum[i]] = {1, 0};
	}

	FFT(coefs1, false);
	FFT(coefs2, false);

	for (int i = 0; i < 8400000; i++)
		coefs1[i] *= coefs2[i];

	FFT(coefs1, true);

    int ans = 0;
    for (int i = acum[s.size()] + 1; i < 8400000; i++)
        if (coefs1[i].real() >= 0.5)
            ans++;

    printf("%d\n", ans);

	return 0;
}
