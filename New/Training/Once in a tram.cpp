#include <bits/stdc++.h>

using namespace std;

int x;

int main() {
    scanf("%d", &x);
    x++;

    while (1) {
        int a = 0, b = 0, aux = x;
        for (int i = 0; i < 6; i++) {
            if (i < 3) a += aux % 10;
            else b += aux % 10;
            aux /= 10;
        }
        if (a == b) break;
        x++;
    }
    printf("%d\n", x);

    return 0;
}
