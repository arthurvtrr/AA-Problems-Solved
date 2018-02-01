#include <bits/stdc++.h>

using namespace std;

int n, q, t, x, y;
string s[100100], news;

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        cin >> s[i];

    for (int i = 0; i < q; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &x, &y);
        }
        else {
            cin >> x >> news;
        }
    }

    return 0;
}

