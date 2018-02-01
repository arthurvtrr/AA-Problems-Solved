#include <bits/stdc++.h>

using namespace std;

int n;
char c;
string s;
bool valid[30];

int main() {
    scanf("%d", &n);

    int ans = 0, cnt = (1 << 26) - 1;

    for (int i = 0; i < n; i++) {
        scanf(" %c", &c);
        cin >> s;

        if (c == '!') {
            int aux = 0;
            for (int j = 0; j < s.size(); j++)
                if (!valid[s[j] - 'a'])
                    aux |= 1 << (s[j] - 'a');
            cnt &= aux;
        }
        else if (c == '.') {
            for (int j = 0; j < s.size(); j++) {
                if (!valid[s[j] - 'a']) {
                    if (cnt & (1 << (s[j] - 'a')))
                        cnt -= 1 << (s[j] - 'a');

                    valid[s[j] - 'a'] = true;
                }
            }
        }
        else {
            if (!valid[s[0] - 'a']) {
                if (cnt & (1 << (s[0] - 'a')))
                    cnt -= 1 << (s[0] - 'a');

                valid[s[0] - 'a'] = true;
            }
        }
        if (__builtin_popcount(cnt) == 1) ans = max(ans, n - i - 2);
    }
    printf("%d\n", ans);

    return 0;
}
