#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int a, b, c;

int main() {
    scanf("%d %d %d", &a, &b, &c);

    int sol = 0;
    while (a >= 1 && b >= 2 && c >= 4) {
        sol += 7;
        a--;
        b -= 2;
        c -= 4;
    }

    printf("%d\n", sol);

    return 0;
}
