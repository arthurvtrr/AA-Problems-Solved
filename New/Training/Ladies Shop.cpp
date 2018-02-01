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

complex < double > aux[2100000];

void FFT(complex < double > *coef, bool inverse) {
	int siz = 1 << ((int) ceil(log2(n+1)));
	siz *= 2;

	for (int i = 0; i < 2100000; i++)
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

int t, m, x, nums[1001000];
complex < double > coefs1[2100000];

int main() {
	scanf("%d %d", &t, &m);

	n = m+1;
	for (int i = 0; i < t; i++) {
        scanf("%d", &x);
        coefs1[x] = {1, 0};
        nums[x] = 1;
	}

	FFT(coefs1, false);

	for (int i = 0; i < 2100000; i++)
		coefs1[i] *= coefs1[i];

	FFT(coefs1, true);

    bool possible = true;
    vector < int > ans;
    for (int i = 1; i <= m; i++) {
        if (nums[i] == 1 && coefs1[i].real() < 0.5) ans.push_back(i);
        else if (nums[i] == 0 && coefs1[i].real() >= 0.5) possible = false;
    }

    if (!possible) printf("NO\n");
    else {
        printf("YES\n");
        printf("%d\n", ans.size());
        for (int i = 0; i < ans.size(); i++) {
            if (i) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
    }

	return 0;
}
