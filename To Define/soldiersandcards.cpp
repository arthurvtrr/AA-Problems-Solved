#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k, x, s = 0;
    queue < int > f1, f2;

    scanf("%d", &n);

    for (int i = 0; i < 2; i++) {
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &x);
            if (i == 0) f1.push(x);
            else f2.push(x);
        }
    }

    while (!f1.empty() && !f2.empty() && s <= 1 << n) {
        int c1 = f1.front();
        int c2 = f2.front();
        f1.pop();
        f2.pop();

        if (c1 > c2) {
            f1.push(c2);
            f1.push(c1);
        }
        else {
            f2.push(c1);
            f2.push(c2);
        }
        s++;
    }

    if (s > 1 << n) printf("-1\n");
    else {
        if (f1.empty()) printf("%d 2\n", s);
        else printf("%d 1\n", s);
    }

    return 0;
}
