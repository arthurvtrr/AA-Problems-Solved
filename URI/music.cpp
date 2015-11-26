#include <stdio.h>

using namespace std;

int main() {
    int t, s, q;
    scanf("%d %d %d", &t, &s, &q);

    int sol = 0;
    while (s < t) {
        s *= q;
        sol++;
    }

    printf("%d\n", sol);

    return 0;
}
