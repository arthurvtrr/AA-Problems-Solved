#include <bits/stdc++.h>

using namespace std;

int t, k;
string s;

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        cin >> s >> k;
        int siz = s.size();
        int flips = 0;
        for (int i = 0; i < siz-k+1; i++)
            if (s[i] == '-') {
                for (int j = 0; j < k; j++) {
                    if (s[i+j] == '-') s[i+j] = '+';
                    else s[i+j] = '-';
                }
                flips++;
            }

        bool possible = true;

        for (int i = 0; i < siz; i++)
            if (s[i] == '-')
                possible = false;

        if (!possible) printf("Case #%d: IMPOSSIBLE\n", tc+1);
        else printf("Case #%d: %d\n", tc+1, flips);
    }

    return 0;
}
