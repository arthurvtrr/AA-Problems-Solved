#include <bits/stdc++.h>

using namespace std;

string s;
int acum[26][100100], cnt[26];

int main() {
    cin >> s;
    for (int i = 0; i < s.size(); i++)
        acum[s[i] - 'a'][i] = 1;

    for (int i = 1; i < 100100; i++)
        for (int j = 0; j < 26; j++)
            acum[j][i] += acum[j][i-1];

    int ini = 1, fim = (int)s.size() - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i <= (int)s.size() - meio; i++) {
            for (int j = 0; j < 26; j++)
                cnt[j] += (acum[j][i+meio-1] - (i == 0? 0 : acum[j][i-1])) > 0;
        }

        bool v = false;
        for (int i = 0; i < 26; i++)
            if (cnt[i] == (int)s.size() - meio + 1)
                v = true;

        if (v) fim = meio-1;
        else ini = meio+1;
    }
    printf("%d\n", ini);

    return 0;
}
