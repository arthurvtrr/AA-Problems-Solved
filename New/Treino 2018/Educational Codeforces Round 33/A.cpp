#include <bits/stdc++.h>

using namespace std;

int n, x, y;

int main() {
    scanf("%d", &n);

    y = 3;
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        if (x == y) {
            printf("NO\n");
            return 0;
        }
        for (int j = 1; j < 4; j++)
            if (j != x && j != y) {
                y = j;
                break;
            }
    }
    printf("YES\n");

    return 0;
}
