#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int n, flowers[220000];
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &flowers[i]);

    sort(flowers, flowers+n);

    if (flowers[n-1] - flowers[0] == 0) {
        long long sum = 0;
        int x = n-1;
        while (x > 0) sum += x--;
        printf("0 %I64d\n", sum);
    } else {
        long long a = 0, b = n-1, dif = flowers[n-1] - flowers[0], timesa = 0, timesb = 0;
        while (flowers[a] == flowers[0]) {
            timesa++;
            a++;
        }
        while (flowers[b] == flowers[n-1]) {
            timesb++;
            b--;
        }

        printf("%I64d %I64d\n", dif, timesa * timesb);
    }

    return 0;
}
