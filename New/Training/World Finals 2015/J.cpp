#include <bits/stdc++.h>

using namespace std;

#define PI acos(-1)
#define EPS 1e-9

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

complex < double > aux[1050000];

void FFT(complex < double > *coef, bool inverse) {
	int siz = 1 << ((int) ceil(log2(n+1)));
	siz *= 2;

	for (int i = 0; i < 1050000; i++)
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

int t, a, b, divs[500500];
complex < double > coefs1[1050000], coefs2[1050000];

int main() {
	n = 500005;

	for (int i = 1; i < 500500; i++)
		for (int j = i; j < 500500; j += i)
			divs[j]++;

	for (int i = 0; i < 500005; i++)
		coefs1[i] = coefs2[i] = {divs[i+1], 0};

	FFT(coefs1, false);
	FFT(coefs2, false);

	for (int i = 0; i < 1050000; i++)
		coefs1[i] *= coefs2[i];

	FFT(coefs1, true);

	scanf("%d", &t);
	for (int i = 0; i < t; i++) {
		scanf("%d %d", &a, &b);
		int maxi = 0, area = 1;
		for (int j = max(2, a); j <= b; j++)
			if (round(coefs1[j-2].real()) > maxi) {
				maxi = round(coefs1[j-2].real());
				area = j;
			}
		printf("%d %d\n", area, maxi);
	}

	return 0;
}
