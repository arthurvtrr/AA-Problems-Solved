#include <bits/stdc++.h>

using namespace std;

int main() {
    string s, t, p = "";
    int d = 0;

    cin >> s;
    cin >> t;

    for (int i = 0; i < s.size(); i++)
        if (s[i] != t[i]) d++;

    if (d % 2 != 0) printf("impossible\n");
    else {
        int c = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) {
                if (c % 2 == 0) p += s[i];
                else p += t[i];
                c++;
            }
            else p += s[i];
        }

        cout << p << endl;
    }
    return 0;
}
