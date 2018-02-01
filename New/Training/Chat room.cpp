#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;
    string look = "hello";

    int pos = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == look[pos]) pos++;
        if (pos == 5) break;
    }

    if (pos == 5) printf("YES\n");
    else printf("NO\n");

    return 0;
}
