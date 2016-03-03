#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    int n, s[5500];

    scanf("%d", &n);

    if (n < 3) {
        printf("1\n");
        printf("1\n");
    }
    else if (n == 3) {
        printf("2\n");
        printf("1 3\n");
    }
    else if (n == 4) {
        printf("3\n");
        printf("1 4 2\n");
    }
    else {
        int x = 1;
        for (int i = 0; i <= n; i += 2) {
            s[i] = x;
            s[i+1] = ceil(n / 2.0) + x;
            x++;
        }

        printf("%d\n", n);

        for (int i = 0; i < n; i++) {
            printf("%d ", s[i]);
        }
        printf("\n");
    }
    return 0;
}
