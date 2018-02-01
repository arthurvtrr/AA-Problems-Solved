#include <bits/stdc++.h>

using namespace std;

int main() {
    int q, n;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &n);
        if (n % 4 == 0) printf("%d\n", n/4);
        else if (n % 4 == 1) printf("%d\n", n/4 > 1? n/4 - 1 : -1);
        else if (n % 4 == 2) printf("%d\n", n/4 > 0? n/4 : -1);
        else printf("%d\n", n/4 > 2? n/4 - 1 : -1);
    }

    return 0;
}
