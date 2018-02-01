#include <bits/stdc++.h>

using namespace std;

int t, n, m, x, y;
long long val[303][303];
string s;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d", &n);
        cin >> s;
        scanf("%d %d %d", &m, &x, &y);

        for (int i = 0; i < 303; i++)
            for (int j = 0; j < 303; j++)
                val[i][j] = 0;

        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                if (j - i <= m + 3)
                    for (int k = i; k <= j; k++) {
                        val[i][j] *= 10;
                        val[i][j] += s[k] - '0';
                    }

        long long ans = 0;

        for (int i = 0; i < 1 << n; i++) {
            long long aux = 0;
            int pos = 0, bit = 0;
            while (pos < n) {
                if (i & (1 << bit) && pos+1 < n) {
                    aux = gcd(aux, val[pos][pos]*10 + val[pos+1][pos+1]);
                    pos += 2;
                }
                else {
                    aux = gcd(aux, val[pos][pos]);
                    pos++;
                }
                bit++;
            }
            if (bit-1 >= x && bit-1 <= y) ans = max(ans, aux);

            if (m == 1) break;
        }

        printf("%lld\n", ans);
    }

    return 0;
}

