#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    scanf("%d", &n);

    int x = 2, y, cont = 0;

    if (n % 2) {
        while (n && cont < 500) {
            printf("1\n");
            fflush(stdout);
            n--;
            if (n == 0) break;

            scanf("%d", &y);
            n -= y;
        }
    }
    else {
        while ((n / x) % 2 == 0) x *= 2;

        while (n && cont < 500) {
            printf("%d\n", x);
            fflush(stdout);
            n -= x;
            if (n == 0) break;

            scanf("%d", &y);
            n -= y;
            if (y % 2) x = 1;
            else x = y;
        }
    }
    return 0;
}

