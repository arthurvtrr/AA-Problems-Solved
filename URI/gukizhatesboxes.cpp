#include <stdio.h>

using namespace std;

int n, m, boxes[110000];
long long sum = 0;

bool possible(long long t) {
    int last = n-1, aux[110000];
    for (int i = 0; i < n; i++) aux[i] = boxes[i];

    for (int i = 0; i < m; i++) {
        while (last >= 0 && aux[last] == 0) last--;
        long long time = t - last - 1;
        if (time <= 0) break;
        while (last >= 0 && aux[last] <= time)
            time -= aux[last--];
        if (last >= 0) aux[last] -= time;
    }
    if (last < 0) return true;
    return false;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &boxes[i]);
        sum += boxes[i];
    }
    long long l = 2, r = n + sum;
    while (l < r) {
        long long mid = (l + r) / 2;
        if (possible(mid)) r = mid;
        else l = mid + 1;
    }

    printf("%I64d\n", r);

    return 0;
}
