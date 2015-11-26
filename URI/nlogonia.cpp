#include <stdio.h>

using namespace std;

int main() {
    int k, n, m, x, y;

    while (1) {
        scanf("%d", &k);
        if (k == 0) break;

        scanf("%d %d", &n, &m);

        for (int i = 0; i < k; i++) {
            scanf("%d %d", &x, &y);
            if (x == n || y == m)
                printf("divisa\n");
            else if (x > n && y > m)
                printf("NE\n");
            else if (x < n && y > m)
                printf("NO\n");
            else if (x < n && y < m)
                printf("SO\n");
            else
                printf("SE\n");
        }
    }

    return 0;
}
