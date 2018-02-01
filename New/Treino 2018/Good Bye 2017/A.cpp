#include <bits/stdc++.h>

using namespace std;

string s;

int main() {
    cin >> s;

    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9' && ((s[i] - '0') % 2))
            ans++;
        else if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u')
            ans++;
    }
    printf("%d\n", ans);

    return 0;
}
