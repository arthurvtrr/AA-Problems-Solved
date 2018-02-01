#include <bits/stdc++.h>

using namespace std;

int n;
string s, orig;

int main() {
    scanf("%d", &n);
    cin >> s;
    orig = s;

    s += '0';

    bool vai_um = true;
    for (int i = 0; i < s.size(); i++)
        if (vai_um) {
            if (s[i] == '0') {
                s[i] = '1';
                vai_um = false;
            }
            else {
                s[i] = '0';
                vai_um = true;
            }
        }

    int ans = 0;
    for (int i = 0; i < orig.size(); i++)
        if (orig[i] != s[i])
            ans++;

    printf("%d\n", ans);

    return 0;
}
