#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int a[220000];
int seg[880000];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = a[ini];
        return;
    }
    int meio = (ini + fim) / 2;
    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);
    seg[id] = seg[2*id] + seg[2*id+1];
}

void update(int id, int ini, int fim, int pos, int val) {
    if (ini == fim) {
        seg[id] = val;
        return;
    }
    int meio = (ini + fim) / 2;
    if (pos <= meio) update(2*id, ini, meio, pos, val);
    else update(2*id+1, meio+1, fim, pos, val);
    seg[id] = seg[2*id] + seg[2*id+1];
}

int query(int id, int ini, int fim, int start, int end) {
    if (end < ini || start > fim) return 0;
    if (ini >= start && fim <= end) return seg[id];
    int meio = (ini + fim) / 2;
    return query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end);
}

int main() {
    int n, x, y, cont = 1;
    char c[5];

    while(1) {
        scanf("%d", &n);

        if (n == 0) break;

        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        build(1, 1, n);
        if (cont > 1) printf("\n");
        printf("Case %d:\n", cont);

        while(1) {
            scanf("%s", &c);
            if (c[0] == 'E') break;
            scanf("%d %d", &x, &y);
            if (c[0] == 'S') update(1, 1, n, x, y);
            else printf("%d\n", query(1, 1, n, x, y));
        }
        cont++;
    }
    return 0;
}
