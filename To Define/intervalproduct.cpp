#include <stdio.h>
#include <algorithm>
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
    seg[id] = fmax(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int pos, int val) {
    if (ini == fim) {
        seg[id] = val;
        return;
    }
    int meio = (ini + fim) / 2;
    if (pos <= meio) update(2*id, ini, meio, pos, val);
    else update(2*id+1, meio+1, fim, pos, val);
    seg[id] = fmax(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (end < ini || start > fim) return -100000;
    if (ini >= start && fim <= end) return seg[id];
    int meio = (ini + fim) / 2;
    return fmax(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

int main() {
    int n, m, t, q, x, y;
    char c[3];

    scanf("%d", &t);
    for (int j = 0; j < t; j++) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);

        build(1, 0, n-1);
        printf("Testcase %d:\n", j);
        scanf("%d", &q);

        for (int i = 0; i < q; i++) {
            scanf("%s", &c);
            if (c[0] == 'B') {
                scanf("%d %d", &x, &y);
                update(1, 0, n-1, x, y);
            }
            else if (c[0] == 'A') {
                scanf("%d", &x);
                m += x;
            }
            else {
                scanf("%d %d", &x, &y);
                printf("%d\n", abs(m - query(1, 0, n-1, x, y)));
            }
        }
        printf("\n");
    }

    return 0;
}
