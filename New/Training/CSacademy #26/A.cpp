#include <bits/stdc++.h>

using namespace std;

int n, k;
set < char > diff;
string s;

int main() {
    scanf("%d %d", &n, &k);
    int ans = -1;

    for (int i = 0; i < n; i++) {
        cin >> s;
        diff.clear();
        for (int j = 0; j < s.size(); j++)
            diff.insert(s[j]);
        if (diff.size() <= k)
            ans = max(ans, (int)s.size());
    }
    printf("%d\n", ans);

    return 0;
}
