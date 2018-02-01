#include <bits/stdc++.h>

using namespace std;

int n, m, c, x, aux[1010];

int main() {
    scanf("%d %d %d", &n, &m, &c);
    for (int i = 0; i < 1010; i++)
        aux[i] = 1010;
    for (int i = 0; i < m; i++) {
        scanf("%d", &x);
        if (x <= c/2) {
            for (int j = 0; j < n; j++)
                if (aux[j] > x) {
                    aux[j] = x;
                    printf("%d\n", j+1);
                    fflush(stdout);
                    break;
                }
        }
        else {
            for (int j = n-1; j >= 0; j--)
                if (aux[j] < x || aux[j] == 1010) {
                    aux[j] = x;
                    printf("%d\n", j+1);
                    fflush(stdout);
                    break;
                }
        }

        bool v = true;
        for (int j = 0; j < n; j++)
            if (aux[j] == 1010)
                v = false;

        if (v) break;
    }
    return 0;
}


