#include <bits/stdc++.h>

using namespace std;

int n, m, k, x;
set < int > groups[10100], neg[10100];

int main() {
    scanf("%d %d", &n, &m);

    bool cancel = false;

    for (int i = 0; i < m; i++) {
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &x);
            if (x > 0) groups[i].insert(x);
            else neg[i].insert(x);
        }
        bool valid = false;

        for (auto it : groups[i])
            if (neg[i].count(-it))
                valid = true;

        if (!valid) cancel = true;
    }

    if (cancel) printf("YES\n");
    else printf("NO\n");

    return 0;
}

