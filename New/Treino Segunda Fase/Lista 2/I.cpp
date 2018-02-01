#include <bits/stdc++.h>

using namespace std;

string s;
int cnt[10];

int main() {
    while (1) {
        cin >> s;
        if (s == "*") break;
        for (int i = 0; i < s.size(); i++)
            if (s[i] == 'A')
                s[i] = '1';

        memset(cnt, 0, sizeof cnt);
        bool valid = true;

        int lft = 16, siz = 16, pos = 0;
        while (pos < s.size()) {
            for (int i = pos; i < min((int)s.size(), pos+siz); i++) {
                if (s[i] >= '0' && s[i] <= '9')
                    cnt[s[i] - '0']++;
                lft--;
            }

            if (lft == 4) {
                bool g = false;
                for (int i = 0; i < 10; i++)
                    if (cnt[i])
                        g = true;
                if (!g) break;
            }

            bool rem = cnt[0];
            lft += cnt[0];
            cnt[0] = 0;

            for (int i = 1; i < 5; i++) {
                int x = min(cnt[i], cnt[10-i]);
                if (x > 0) {
                    rem = true;
                    cnt[i] -= x;
                    cnt[10-i] -= x;
                    lft += x * 2;
                }
            }
            if (cnt[5] / 2 > 0) {
                rem = true;
                lft += cnt[5] / 2 * 2;
                cnt[5] -= cnt[5] / 2 * 2;
            }

            if (!rem) { valid = false; break; }
            pos += siz;
            siz = lft;
        }

        for (int i = 0; i < 10; i++)
            if (cnt[i])
                valid = false;

        if (valid) printf("Y\n");
        else printf("N\n");
    }
    return 0;
}
