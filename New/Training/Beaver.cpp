#include <bits/stdc++.h>

using namespace std;

int n, lens[100100][11];
string s, subs[11];

void Zfunction(string s, int ind) {
    int n = s.size();
    int L = 0, R = 0;

    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R-L] == s[R]) R++;
            lens[i][ind] = R-L;
            R--;
        }
        else {
            if (lens[i-L][ind] < R-i+1)
                lens[i][ind] = lens[i-L][ind];
            else {
                L = i;
                while (R < n && s[R-L] == s[R]) R++;
                lens[i][ind] = R-L;
                R--;
            }
        }
    }
}

int main() {
    cin >> s;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> subs[i];
        string x = subs[i];
        x += '$';
        x += s;
        Zfunction(x, i);
    }

    int len = 0, pos = 0, ini = 0, fim = 0;
    multiset < int > limits;

    while (fim < s.size()) {
        for (int j = 0; j < n; j++) {
            int siz = subs[j].size();
            if (lens[fim + siz + 1][j] == siz)
                limits.insert(fim + siz - 1);
        }

        int limit;
        if (limits.empty()) limit = s.size();
        else limit = *(limits.begin());

        if (fim == limit) {
            if (fim - ini > len) {
                len = fim - ini;
                pos = ini;
            }

            while (1) {
                for (int j = 0; j < n; j++) {
                    int siz = subs[j].size();
                    if (lens[ini + siz + 1][j] == siz)
                        limits.erase(limits.find(ini + siz - 1));
                }
                ini++;

                if (limits.empty()) limit = s.size();
                else limit = *(limits.begin());

                if (limit > fim) break;
            }
            fim++;
        }
        else fim++;
    }

    int limit;
    if (limits.empty()) limit = s.size();
    else limit = *(limits.begin());

    if (fim == limit && fim - ini > len) {
        len = fim - ini;
        pos = ini;
    }

    printf("%d %d\n", len, pos);

    return 0;
}
