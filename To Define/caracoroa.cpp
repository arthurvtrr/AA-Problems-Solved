#include <stdio.h>

using namespace std;

int main() {
    int a, t, m, j;

    while (1) {
        m = 0, j = 0;
        scanf("%d", &t);
        if (t == 0) break;

        for (int i = 0; i < t; i++) {
            scanf("%d", &a);
            if (a == 0) m++;
            else j++;
        }

        printf("Mary won %d times and John won %d times\n", m, j);
    }
    return 0;
}
