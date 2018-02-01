#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, q, t, k, d;
int last[110];

int main() {
    scanf("%d %d", &n, &q);

    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &t, &k, &d);
        int cont = 0;
        for (int i = 1; i <= n; i++)
            if (last[i] < t)
                cont++;

        if (cont < k) printf("-1\n");
        else {
            int sum = 0, left = k;
            for (int i = 1; i <= n; i++)
                if (last[i] < t) {
                    left--;
                    sum += i;
                    last[i] = t + d - 1;
                    if (left == 0) break;
                }

            printf("%d\n", sum);
        }
    }
    return 0;
}
