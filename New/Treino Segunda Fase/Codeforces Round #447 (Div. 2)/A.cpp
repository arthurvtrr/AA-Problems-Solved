#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;

    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'A') {
            int cntb = 0, cnta = 0;
            for (int j = 0; j < i; j++)
                cntb += s[j] == 'Q';
            for (int j = i+1; j < s.size(); j++)
                cnta += s[j] == 'Q';
            ans += cntb * cnta;
        }
    }
    printf("%d\n", ans);

    return 0;
}
