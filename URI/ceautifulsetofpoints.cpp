#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, m, x = 0, y = 0;
    scanf("%d %d", &n, &m);

    if (n > m) x++;
    else y++;

    printf("%d\n", 1 + min(n,m));
    while (x <= n && y <= m)
        printf("%d %d\n", x++, y++);

    if (n == m) printf("%d 0\n", n);

    return 0;
}
