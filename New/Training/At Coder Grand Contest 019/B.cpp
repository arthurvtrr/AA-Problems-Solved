#include <bits/stdc++.h>

using namespace std;

string s;
long long n, cnt[30];

int main() {
    cin >> s;
    n = s.size();

    long long ans = n * (n+1) / 2;
    ans -= n-1;

    for (int i = 0; i < n; i++)
        cnt[s[i] - 'a']++;

    for (int i = 0; i < 30; i++)
        ans -= cnt[i] * (cnt[i]-1) / 2;

    printf("%lld\n", ans);

    return 0;
}

