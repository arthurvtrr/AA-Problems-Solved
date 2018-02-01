#include <bits/stdc++.h>

using namespace std;

const int S = 26;
const int N = 100010;
const double PI = acos(-1.0);

char buffer[N];

typedef complex<double> doublex;

void fft(vector<doublex> &poly, bool inverse) {
  int len = poly.size(), n = log2(len);
  for (int i = 0; i < len; ++i) {
    int j = 0, k = i, log = n - 1;
    while (k) {
      if (k & 1) {
        j += 1 << log;
      }
      k >>= 1;
      --log;
    }
    if (i < j) {
      swap(poly[i], poly[j]); 
    }
  }
  for (int i = 1; i <= n; ++i) {
    int m = 1 << i;
    double angle = 2 * PI * (inverse ? -1 : 1) / m;
    doublex unity_root = doublex(cos(angle), sin(angle));
    for (int j = 0; j < len; j += m) {
      doublex omega = 1;
      for (int k = 0; k < (m >> 1); ++k) {
        doublex t = omega * poly[j + k + (m >> 1)];
        doublex u = poly[j + k];
        poly[j + k] = u + t;
        poly[j + k + (m >> 1)] = u - t;
        omega *= unity_root;
      }
    }
  }
  if (inverse) {
    for (int i = 0; i < len; ++i) {
      poly[i] /= len;
    }
  }
}

vector<doublex> multiply(const vector<doublex> &a, const vector<doublex> &b) {
  int n = a.size(), m = b.size();
  int len = 1 << ((int) ceil(log2(max(n, m) + 1)) + 1);
  vector<doublex> fa(len, 0), fb(len, 0);
  for (int i = 0; i < n; ++i) {
    fa[i] = a[i];
  }
  for (int i = 0; i < m; ++i) {
    fb[i] = b[i];
  }
  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < len; ++i) {
    fa[i] *= fb[i];
  }
  fft(fa, true);
  return fa;
}

int sum[N];

int main() {
  scanf("%s", buffer + 1);
  int len = strlen(buffer + 1);
  for (int i = 1; i <= len; ++i) {
    sum[i] = (buffer[i] - 'a' + 1) + sum[i - 1];
  }
  vector<doublex> a(sum[len] + 1, 0.0), b(sum[len] + 1, 0.0);
  for (int i = 0; i <= len; ++i) {
    a[sum[i]] = 1.0;
    b[sum[len] - sum[i]] = 1.0;
  }
  int asw = 0;
  vector<doublex> poly_asw = multiply(a, b);
  for (int i = sum[len] + 1; i < poly_asw.size(); ++i) {
    asw += ((int)round(poly_asw[i].real()) >= 1);
  }
  return !printf("%d\n", asw);
}
