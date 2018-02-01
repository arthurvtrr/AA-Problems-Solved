#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, k, s, t, cs[200200], vs[200200];
long long gas[200200];

int main() {
    scanf("%d %d %d %d", &n, &k, &s, &t);

    for (int i = 0; i < n; i++)
        scanf("%d %d", &cs[i], &vs[i]);

    for (int i = 0; i < k; i++)
        scanf("%lld", &gas[i]);
    gas[k] = s;

    sort(gas, gas+k+1);

    long long ini = 1, fim = 2000000200;

    while (ini <= fim) {
        int mid = (ini + fim) / 2;

        long long time = 0;
        int last = 0;

        for (int i = 0; i <= k; i++) {
            int dist = gas[i] - last;

            if (mid < dist) {
                time = 2000000200;
                break;
            }
            else {
                time += 2*dist - min(dist, mid - dist);
            }

            last = gas[i];
        }


        if (time > t) ini = mid + 1;
        else fim = mid - 1;
    }

    int sol = 2000000200;
    for (int i = 0; i < n; i++)
        if (vs[i] >= ini)
            sol = min(sol, cs[i]);

    printf("%d\n", sol == 2000000200? -1 : sol);

    return 0;
}
