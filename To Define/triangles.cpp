#include <stdio.h>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    int n, d[110000];
    while (scanf("%d", &n) != EOF) {
        map < int, int > dists;
        int total = 0, a;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            dists[total];
            d[i] = total;
            total += a;
        }
        if (total % 3 != 0) {
            printf("0\n");
            continue;
        }
        int sol = 0;
        for (int i = 1; i <= n; i++)
            if (dists.count(d[i]) && dists.count(d[i] + total / 3) && dists.count(d[i] + total / 3 * 2)) sol++;
        printf("%d\n", sol);
    }
    return 0;
}
