#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll a, m, p, q, r, s;
vector < ll > quant[33];
ll powm[33];
vector < vector < string > > valid;

string getStr(ll x) {
    if (x == 0) return "0";

    string ret = "";
    while (x) {
        ret += (x % 10) + '0';
        x /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

bool cmp(vector < string > a, vector < string > b) {
    for (int i = 0; i < min(a.size(), b.size()); i++) {
        if (a[i].back() == 'A' && b[i].back() == 'M') return true;
        if (a[i].back() == 'M' && b[i].back() == 'A') return false;

        ll c = 0, d = 0;
        for (int j = 0; j < a[i].size()-1; j++) {
            c *= 10;
            c += a[i][j] - '0';
        }
        for (int j = 0; j < b[i].size()-1; j++) {
            d *= 10;
            d += b[i][j] - '0';
        }

        if (c < d) return true;
        else if (c > d) return false;
    }
    return true;
}

int main() {
    int t = 1;
    while (1) {
        scanf("%lld %lld %lld %lld %lld %lld", &a, &m, &p, &q, &r, &s);
        if (a + m + p + q + r + s == 0) break;

        if (p >= r && q <= s) {
            printf("Case %d: empty\n", t++);
            continue;
        }

        powm[0] = 1;
        for (int i = 1; i < 33; i++) {
            powm[i] = m * powm[i-1];
            if (powm[i] > 1000000000) break;
        }

        for (int i = 0; i < 33; i++)
            quant[i].clear();
        valid.clear();

        for (int i = 0; i < 33 && q <= s / powm[i]; i++) {
            ll mini = max(0LL, r - (p * powm[i])), maxi = s - (q * powm[i]);

            for (int j = i; j >= 0; j--) {
                if (mini <= 0) {
                    quant[i].push_back(0);
                    continue;
                }

                ll k = (mini + powm[j] * a - 1) / (powm[j] * a);

                if (k * powm[j] * a > maxi) {
                    quant[i].push_back(k-1);
                    mini -= (k-1) * a * powm[j];
                    maxi -= (k-1) * a * powm[j];
                }
                else {
                    quant[i].push_back(k);
                    mini -= k * a * powm[j];
                    maxi -= k * a * powm[j];
                }
            }
        }

        ll mini = LLONG_MAX;
        for (int i = 0; i < 33 && q <= s / powm[i]; i++) {
            ll np = p, nq = q, x = i;
            for (int j = 0; j <= i; j++) {
                np += quant[i][j] * a;
                nq += quant[i][j] * a;
                x += quant[i][j];

                if (j != i) {
                    np *= m; nq *= m;
                }
            }

            if (np >= r && nq <= s)
                mini = min(mini, x);
        }

        for (int i = 0; i < 33 && q <= s / powm[i]; i++) {
            ll np = p, nq = q, x = i;
            for (int j = 0; j <= i; j++) {
                np += quant[i][j] * a;
                nq += quant[i][j] * a;
                x += quant[i][j];

                if (j != i) {
                    np *= m; nq *= m;
                }
            }

            if (np >= r && nq <= s && x == mini) {
                vector < string > aux;

                int cnt = 0;
                for (int j = 0; j <= i; j++) {
                    if (quant[i][j] != 0) {
                        if (cnt) { aux.push_back(getStr(cnt) + 'M'); cnt = 0; }
                        aux.push_back(getStr(quant[i][j]) + 'A');
                    }
                    if (j != i) cnt++;
                }

                if (cnt) aux.push_back(getStr(cnt) + 'M');
                valid.push_back(aux);
            }
        }

        if (valid.empty()) printf("Case %d: impossible\n", t++);
        else {
            sort(valid.begin(), valid.end(), cmp);
            printf("Case %d:", t++);
            for (string s : valid[0])
                cout << " " << s;
            printf("\n");
        }

    }

    return 0;
}
