#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, m, x;
    while (scanf("%d %d", &n, &m) != EOF) {
        int sol = 0;
        for (int i = 0; i < n; i++) {
            int cont = 0;
            for (int j = 0; j < m; j++) {
                scanf("%d", &x);
                if (x > 0) cont++;
            }
            if (cont == m) sol++;
        }
        printf("%d\n", sol);
    }
    return 0;
}
