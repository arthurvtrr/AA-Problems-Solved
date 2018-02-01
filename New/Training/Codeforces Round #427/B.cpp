#include <bits/stdc++.h>

using namespace std;

int k;
string s;

int main() {
    scanf("%d", &k);
    cin >> s;
    sort(s.begin(), s.end());

    int ans = 0, atual = 0;
    for (int i = 0; i < s.size(); i++)
        atual += s[i] - '0';

    for (int i = 0; i < s.size(); i++) {
        if (atual >= k) break;
        atual += 9 - (s[i] - '0');
        ans++;
    }
    printf("%d\n", ans);

    return 0;
}

