#include <bits/stdc++.h>

using namespace std;

map < int, int > cnt;
int t, x;

int main() {
    scanf("%d", &t);
    while (t--) {
        cnt.clear();
        for (int i = 0; i < 4; i++) {
            scanf("%d", &x);
            cnt[x]++;
        }
        if (cnt.size() == 1 || (cnt.size() == 2 && cnt.begin()->second == 2)) printf("YES\n");
        else printf("NO\n");
    }
}
