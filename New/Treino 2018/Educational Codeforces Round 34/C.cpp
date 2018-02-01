#include <bits/stdc++.h>

using namespace std;

map < int, int > cnt;
int n, x;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        cnt[x]++;
    }
    int ans = 0;
    for (auto it : cnt)
        ans = max(ans, it.second);
    printf("%d\n", ans);

    return 0;
}
