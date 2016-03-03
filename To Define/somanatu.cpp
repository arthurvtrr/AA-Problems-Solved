#include <stdio.h>

using namespace std;

int main() {

    unsigned long long a, b;
    scanf("%lli %lli", &a, &b);

    unsigned long long sol = (a + b) * (b - a + 1) / 2;
    printf("%lli\n", sol);

    return 0;
}
