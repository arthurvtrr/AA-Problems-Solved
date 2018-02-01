#include <bits/stdc++.h>

using namespace std;

string g, s, q;
int n;
bool good[30], ast;

int main() {
    cin >> g;
    for (int i = 0; i < g.size(); i++)
        good[g[i] - 'a'] = true;

    cin >> s;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '*')
            ast = true;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cin >> q;
        bool valid = true;
        if (ast && q.size() < s.size() - 1) valid = false;
        else if (!ast && q.size() != s.size()) valid = false;

        if (valid) {
            int pos = 0;
            for (int j = 0; j < s.size(); j++) {
                if (s[j] == '*') {
                    for (int k = 0; k < q.size() - (s.size() - 1); k++) {
                        if (good[q[pos] - 'a'])
                            valid = false;
                        pos++;
                    }
                }
                else if (s[j] == '?') {
                    if (!good[q[pos] - 'a'])
                        valid = false;
                    pos++;
                }
                else {
                    if (s[j] != q[pos])
                        valid = false;
                    pos++;
                }
            }
        }
        if (valid) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}


