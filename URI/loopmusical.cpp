#include <stdio.h>

using namespace std;

int main() {
    int n, p, m[11000];

    while (1) {
        p = -1;
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; i++)
            scanf("%d", &m[i]);

        m[n] = m[0];
        m[n+1] = m[1];

        int x = 0;
        for (int i = 1; i <= n+1; i++) {
            if (m[i] < m[i-1] && x != -1) {
                p++;
                x = -1;
            }
            else if (m[i] > m[i-1] && x != 1) {
                p++;
                x = 1;
            }
        }

        printf("%d\n", p);
    }

    return 0;
}
