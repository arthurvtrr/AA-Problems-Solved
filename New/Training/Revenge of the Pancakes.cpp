#include <bits/stdc++.h>

using namespace std;

int t;
string s;

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        cin >> s;
        int ans = 0;
        for (int i = 1; i < s.size(); i++)
            if (s[i] != s[i-1])
                ans++;

        if (s[s.size()-1] == '-') ans++;
        printf("Case #%d: %d\n", tc+1, ans);
    }

    return 0;
}
