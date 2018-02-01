#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n;

int main() {
    scanf("%d", &n);

    int a = 0, b = 0;

    for (int i = 1; i <= n; i++) {
        if (n % i == 0 && i <= n / i) {
            a = i;
            b = n / i;
        }
    }

    printf("%d %d\n", a, b);
    return 0;
}
