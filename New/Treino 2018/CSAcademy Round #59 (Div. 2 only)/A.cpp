#include <bits/stdc++.h>

using namespace std;

int n, cnt[300];
string s;

int main() {
    cin >> n >> s;
    for (int i = 0; i < s.size(); i++)
        cnt[s[i]]++;
    int ans = -1;
    for (int i = 0; i < s.size(); i++)
        if (cnt[s[i]] == 1) {
            ans = s[i];
            break;
        }
    if (ans == -1) printf("-1\n");
    else printf("%c\n", ans);

    return 0;
}
