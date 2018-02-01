#include <bits/stdc++.h>

using namespace std;

#define MOD 7340033
#define ll long long
#define PI acos(-1)

typedef unsigned uint;

template<typename Double>
struct FFT {
	typedef complex<Double> doublex;

	vector<doublex> fft(vector<doublex> y, bool invert = false) {
		const int N = y.size();
		assert(N == (N&-N));
		vector<int> rev(N);
		for (int i = 1; i < N; i++) {
			rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? N >> 1 : 0);
			if (rev[i] < i) swap(y[i], y[rev[i]]);
		}
		vector<doublex> rootni(N / 2);
		for (int n = 2; n <= N; n *= 2) {
			const doublex rootn = polar((Double)1.0, (invert ? +1.0 : -1.0)*2.0*Double(PI) / n);
			rootni[0] = 1.0;
			for (int i = 1; i < n / 2; i++) rootni[i] = rootni[i - 1] * rootn;
			for (int left = 0; left != N; left += n) {
				const int mid = left + n / 2;
				for (int i = 0; i < n / 2; i++) {
					const doublex temp = rootni[i] * y[mid + i];
					y[mid + i] = y[left + i] - temp;
					y[left + i] += temp;
				}
			}
		}
		if (invert) for (auto &v : y) v /= (doublex)N;
		return move(y);
	}

	uint nextpow2(uint v) {
		if (!v) return 1;
		v = 2 * v - 1;
		uint u = 1;
		while (v) {
			u <<= 1;
			v >>= 1;
		}
		return u;
	}

	vector<doublex> convolution(vector<doublex> a, vector<doublex> b) {
		const int n = max((int)a.size() + (int)b.size() - 1, 0), n2 = nextpow2(n);
		a.resize(n2);
		b.resize(n2);
		vector<doublex> fa = fft(move(a)), fb = fft(move(b)), &fc = fa;
		for (int i = 0; i < n2; i++) fc[i] = fc[i] * fb[i];
		vector<doublex> c = fft(move(fc), true);
		c.resize(n);
		return move(c);
	}

	vector<int> polymult(const vector<int> &a, const vector<int> &b, int mod, int npart = 2) {
		if (a.empty() || b.empty()) return{};
		const int div = pow(mod + 1, 1.0 / npart) + 4, n = nextpow2(a.size() + b.size() - 1);
		vector<vector<doublex>> splita(npart, vector<doublex>(n)), splitb(npart, vector<doublex>(n));
		for (int i = 0; i < (int)a.size(); i++) {
			int v = a[i];
			for (int j = 0; j < npart; j++) splita[j][i] = v%div, v /= div;
		}
		for (int i = 0; i < (int)b.size(); i++) {
			int v = b[i];
			for (int j = 0; j < npart; j++) splitb[j][i] = v%div, v /= div;
		}
		for (int i = 0; i < npart; i++) {
			splita[i] = fft(move(splita[i]));
			splitb[i] = fft(move(splitb[i]));
		}
		vector<int> result(a.size() + b.size() - 1);
		vector<doublex> res(n);
		for (int i = 0; i < npart; i++) for (int j = 0; j < npart; j++) {
			int multby = 1;
			for (int k = 0; k < i + j; k++) multby = (ll)multby*div%mod;
			for (int k = 0; k < n; k++) res[k] = splita[i][k] * splitb[j][k];
			res = fft(move(res), true);
			for (int k = 0; k < (int)result.size(); k++) result[k] = (result[k] + (ll)round(res[k].real()) % mod*multby) % mod;
		}
		return move(result);
	}

	vector<doublex> cyclic_convolution(vector<doublex> a, vector<doublex> b) {
		assert(a.size() == b.size());
		int n = a.size();
		vector<doublex> c = convolution(move(a), move(b));
		for (int i = c.size() - 1; i >= n; --i)c[i - n] += c[i];
		c.resize(n);
		return move(c);
	}
};

