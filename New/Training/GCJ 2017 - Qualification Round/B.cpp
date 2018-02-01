#include <bits/stdc++.h>

using namespace std;

int t;
string s;

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        cin >> s;

        for (int i = (int)s.size() - 1; i >= 1; i--)
            if (s[i] < s[i-1]) {
                s[i-1]--;

                for (int j = i; j < s.size(); j++)
                    s[j] = '9';
            }

        long long ans = 0;
        for (int i = 0; i < s.size(); i++) {
            ans *= 10;
            ans += s[i] - '0';
        }

        printf("Case #%d: %lld\n", tc+1, ans);
    }

    return 0;
}
