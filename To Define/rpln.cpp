#include <stdio.h>
#include <math.h>

using namespace std;

int a[110000];
int seg[440000];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = a[ini];
        return;
    }

    int meio = (ini + fim) / 2;
    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);
    seg[id] = fmin(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (end < ini || start > fim) return 10000000000;
    if (ini >= start && fim <= end) return seg[id];

    int meio = (ini + fim) / 2;

    return fmin(query(2*id+1, meio+1, fim, start, end), query(2*id, ini, meio, start, end));
}

int main() {
    int t, n, q;
    scanf("%d", &t);

    for (int i = 1; i <= t; i++) {
        scanf("%d %d", &n, &q);

        for (int j = 1; j <= n; j++)
            scanf("%d", &a[j]);

        build(1, 1, n);

        printf("Scenario #%d:\n\n", i);

        int x, y;
        for (int k = 0; k < q; k++) {
            scanf("%d %d", &x, &y);
            int s = query(1, 1, n, x, y);
            printf("%d\n\n", s);
        }

    }
    return 0;
}

