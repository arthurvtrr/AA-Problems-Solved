#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define ll long long
#define MOD 1000000007
#define P 41

string s[4];
ll hashs[4][100100], hashF[200200];
int siz1, siz2, siz3, sizF;

ll fast_pow(ll base, ll expo) {
    if (expo < 1) return 1;

    ll result = fast_pow(base, expo/2);
    result *= result;
    result %= MOD;

    if (expo % 2 != 0) result *= base;

    return result % MOD;
}

void calc_hash() {
    for (int h = 1; h < 4; h++) {
        ll aux = 0;
        for (int i = 0; i < s[h].size(); i++) {
            aux += s[h][i] * fast_pow(P, i);
            aux %= MOD;
            hashs[h][i] = aux;
        }
    }
}

int main() {
    cin >> s[1] >> s[2] >> s[3];
    siz1 = s[1].size(); siz2 = s[2].size(); siz3 = s[3].size();

    calc_hash();

    int reused = 0;

    for (int i = 1; i < 4; i++)
        for (int j = 1; j < 4; j++)
            for (int k = 1; k < 4; k++)
                if (i != j && i != k && j != k) {
                    int gain1 = 0, ind1 = 0, gain2 = 0;

                    for (int m = 1; m <= siz1; m++) {
                        ll aux = (hashs[i][siz1-1] - (siz1-m-1 >= 0? hashs[i][siz1-m-1] : 0)) * fast_pow(P, max(0, siz1-m-1) * (MOD-2));
                        aux = ((aux % MOD) + MOD) % MOD;

                        cout << aux << " " << hashs[j][min(m-1, siz2)] << endl;

                        if (aux == hashs[j][min(m-1, siz2)] && min(m-1, siz2) > gain1) {
                            gain1 = min(m-1, siz2);
                            ind1 = siz1-m;
                        }
                    }

                    string first = "";
                    for (int m = 0; m < ind1; m++)
                        first += s[i][m];
                    first += s[j];
                    for (int m = ind1 + siz2; m < siz1; m++)
                        first += s[i][m];

                    cout << first << endl;
                    cout << gain1 << endl;

                    sizF = first.size();

                    ll aux = 0;
                    for (int m = 0; m < sizF; i++) {
                        aux += first[m] * fast_pow(P, m);
                        aux %= MOD;
                        hashF[m] = aux;
                    }

                    for (int m = 0; m < sizF; m++) {
                        ll aux = (hashF[sizF-1] - (sizF-m-1 >= 0? hashF[sizF-m-1] : 0)) * fast_pow(P, max(0, sizF-m-1) * (MOD-2));
                        aux = ((aux % MOD) + MOD) % MOD;

                        if (aux == hashs[k][min(m, siz3)] && min(m, siz3) > gain2)
                            gain2 = min(m, siz3);
                    }

                    reused = max(gain1 + gain2, reused);
                }

    printf("%d\n", siz1 + siz2 + siz3 - reused);

    return 0;
}
