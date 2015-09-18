#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    int n, x, sol = 0;
    scanf("%d %d", &n, &x);

    for (int i = 1; i <= (int)sqrt(x); i++) {
        if (i == sqrt(x) && i <= n) sol++;
        else if (x % i == 0 && x / i <= n) sol += 2;
    }

    printf("%d\n", sol);
    return 0;
}
