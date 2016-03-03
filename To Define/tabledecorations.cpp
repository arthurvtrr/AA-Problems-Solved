#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int c[5];
    scanf("%d %d %d", &c[0], &c[1], &c[2]);
    sort(c, c+3);

    int sol = c[0];
    if (c[1] - c[0] <= (c[2] - c[0]) / 2 && (c[2] - c[0]) / 2 > 0) sol += c[1] - c[0];
    else if ((c[2] - c[0]) / 2 > 0) sol += (c[2] - c[0]) / 2 + ((c[2] - c[0]) % 2 == 0? 0 : 1);

    printf("%d\n", sol);
    return 0;
}
