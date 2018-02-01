#include <bits/stdc++.h>

using namespace std;

int n, m;

int main() {
    scanf("%d %d", &n, &m);
    int day = 1, socks = n;
    while (1) {
        socks--;
        if (day % m == 0) socks++;

        if (socks == 0) break;

        day++;
    }
    printf("%d\n", day);

    return 0;
}
