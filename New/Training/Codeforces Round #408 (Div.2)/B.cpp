#include <bits/stdc++.h>

using namespace std;

int n, m, k, x, y;
bool hole[1001000];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < m; i++) {
        scanf("%d", &x);
        hole[x] = true;
    }

    if (hole[1]) printf("1\n");
    else {
        int pos = 1;
        for (int i = 0; i < k; i++) {
            scanf("%d %d", &x, &y);

            if (pos == x) {
                pos = y;
                if (hole[y]) break;
            }
            else if (pos == y) {
                pos = x;
                if (hole[x]) break;
            }
        }
        printf("%d\n", pos);
    }

    return 0;
}
