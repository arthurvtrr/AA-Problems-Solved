#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, k;

int main() {
    scanf("%d %d", &n, &k);

    int left = 240 - k, sol = 0;
    for (int i = 1; i <= n; i++) {
        if (5*i <= left) {
            left -= 5*i;
            sol++;
        }
        else {
            break;
        }
    }

    printf("%d\n", sol);

    return 0;
}
