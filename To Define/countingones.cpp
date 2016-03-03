#include <stdio.h>

using namespace std;

int main() {
    long long a, b, sol;
    scanf("%lld %lld", &a, &b);

    long long x = 1, pot = 2;
    while (pot <= b) {
        pot *= 2;
        x++;
    }
    printf("%d\n", x);

    sol = x * (b - a + 1) / 2;
    if ((b - a - 1) % 2 != 0) sol--;
    printf("%lld\n", sol);
    return 0;
}
