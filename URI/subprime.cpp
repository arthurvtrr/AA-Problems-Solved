#include <stdio.h>

using namespace std;

int b, n;
int banks[30];

int main() {
    while(1) {
        scanf("%d %d", &b, &n);
        if (b == 0 && n == 0)
            break;

        int d, c, v;

        for (int i = 1; i <= b; i++)
            scanf("%d", &banks[i]);

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &d, &c, &v);
            banks[d] -= v;
            banks[c] += v;
        }


        bool possible = true;
        for (int i = 1; i <= b; i++)
            if (banks[i] < 0)
                possible = false;

        if (possible)
            printf("S\n");
        else
            printf("N\n");

    }

    return 0;
}
