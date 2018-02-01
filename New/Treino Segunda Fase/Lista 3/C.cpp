#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define EPS 1e-6
#define pii pair < ll, ll >

ll a1, b1, c1, d1, a2, b2, c2, d2;

ll gcd(ll a, ll b) { if (b == 0) return a; return gcd(b, a % b); }

int main() {
	while (1) {
		scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &a1, &b1, &c1, &d1, &a2, &b2, &c2, &d2);
		if (a1 == 0 && b1 == 0 && c1 == 0 && d1 == 0 && a2 == 0 && b2 == 0 && c2 == 0 && d2 == 0) break;

		vector < pii > cand;

		ll tn = b2 - b1;
		ll td = a1 - a2;

		if (tn == 0 && td == 0) {
            ll d = c1 - c2;
            ll n = d2 - d1;

            if (d < 0) {
                while (n > 0) n -= 360;
                while (n + 360 <= 0) n += 360;
            }
            else {
                while (n < 0) n += 360;
                while (n - 360 >= 0) n -= 360;
            }

            if (d || n) { cand.push_back(pii(n / gcd(n, d), d / gcd(n, d))); }
            else { printf("0 1\n"); continue; }
        }

        long double t = tn; t /= td;
        long double x = c1*t + d1, y = c2*t + d2;
        long double aux = fabs(x - y) / 360.0;
        if (fabs(a1*t + b1) < EPS || fabs(aux - round(aux)) < EPS) { cand.push_back(pii(tn / gcd(tn, td), td / gcd(tn, td))); }

		tn = -b2 - b1;
		td = a1 + a2;

		if (tn == 0 && td == 0) {
            ll d = c1 - c2;
            ll n = d2 - d1 + 180;

            if (d < 0) {
                while (n > 0) n -= 360;
                while (n + 360 <= 0) n += 360;
            }
            else {
                while (n < 0) n += 360;
                while (n - 360 >= 0) n -= 360;
            }

            if (d || n) { cand.push_back(pii(n / gcd(n, d), d / gcd(n, d))); }
            else { printf("0 1\n"); continue; }
        }

		t = tn; t /= td;
        x = c1*t + d1, y = c2*t + d2;
        aux = fabs(x - y) / 360.0;
        if (fabs(a1*t + b1) < EPS || fabs(fabs(aux - round(aux)) - 0.5) < EPS) { cand.push_back(pii(tn / gcd(tn, td), td / gcd(tn, td))); }

        vector < pii > valids;
        for (int i = 0; i < cand.size(); i++)
            if (cand[i].first >= 0 && cand[i].second > 0)
                valids.push_back(cand[i]);

        if (valids.empty()) printf("0 0\n");
        else {
            pii best = valids[0];
            for (int i = 1; i < valids.size(); i++)
                if (valids[i].first * best.second < best.first * valids[i].second)
                    best = valids[i];

            printf("%lld %lld\n", best.first, best.second);
        }
	}
	return 0;
}
