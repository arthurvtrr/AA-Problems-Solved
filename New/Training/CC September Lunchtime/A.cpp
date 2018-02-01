#include <bits/stdc++.h>

using namespace std;

int t, price[30];
bool app[30];
string s;

int main() {
    scanf("%d", &t);

    while (t--) {
        memset(app, 0, sizeof app);

        for (int i = 0; i < 26; i++)
            scanf("%d", &price[i]);
        cin >> s;
        for (int i = 0; i < s.size(); i++)
            app[s[i] - 'a'] = true;

        int ans = 0;
        for (int i = 0; i < 26; i++)
            if (!app[i])
                ans += price[i];

        printf("%d\n", ans);
    }

    return 0;
}
