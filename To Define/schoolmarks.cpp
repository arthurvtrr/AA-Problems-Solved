#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, k, p, x, y, num;
    scanf("%d %d %d %d %d", &n, &k, &p, &x, &y);

    int l = 0, m = 0, sum = 0, fh = n / 2, lh = (n+1) / 2;
    for (int i = 0; i < k; i++) {
        scanf("%d", &num);
        if (num >= y) m++;
        else l++;
        sum += num;
    }

    int n1 = min(fh - l, n - k);
    if (l >= lh) printf("-1\n");
    else if (sum + n1 + ((n - n1 - l - m) * y) > x) printf("-1\n");
    else {
        for (int i = 0; i < n1; i++)
            printf("1 ");
        for (int i = 0; i < n - n1 - l - m; i++) {
            if (i > 0) printf(" ");
            printf("%d", y);
        }
        printf("\n");
    }

    return 0;
}
