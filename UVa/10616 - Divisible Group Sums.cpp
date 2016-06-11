#include <stdio.h>
#include <algorithm>

using namespace std;

int n, q, d, m;
long long nums[220];

int main() {
    int cont = 1;

    while (1) {
        scanf("%d %d", &n, &q);
        if (n + q == 0) break;

        for (int i = 0; i < n; i++)
            scanf("%lld", &nums[i]);

        printf("SET %d:\n", cont++);

        for (int i = 0; i < q; i++) {
            scanf("%d %d", &d, &m);

        }
    }
    return 0;
}
