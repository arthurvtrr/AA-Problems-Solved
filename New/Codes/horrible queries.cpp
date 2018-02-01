#include <stdio.h>
#include <algorithm>

using namespace std;

struct Node {
    long long val = 0;
    long long acum = 0;
} seg[400400];

void update(int id, int ini, int fim, int start, int end, long long val) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[id].acum += val;
        return;
    }

    int meio = (ini + fim) / 2;
    seg[2*id].acum += seg[id].acum;
    seg[2*id+1].acum += seg[id].acum;
    seg[id].val += seg[id].acum * (fim - ini + 1);
    seg[id].acum = 0;

    update(2*id, ini, meio, start, end, val);
    update(2*id+1, meio+1, fim, start, end, val);

    seg[id].val += val * (min(fim,end) - max(ini,start) + 1);
}

long long query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id].val + seg[id].acum * (fim - ini + 1);

    int meio = (ini + fim) / 2;

    seg[2*id].acum += seg[id].acum;
    seg[2*id+1].acum += seg[id].acum;
    seg[id].val += seg[id].acum * (fim - ini + 1);
    seg[id].acum = 0;

    return query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end);
}

int main() {
    int t;
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {
        for (int i = 0; i < 400400; i++) {
            seg[i].val = seg[i].acum = 0;
        }

        int n, c, op, p, q;
        long long v;
        scanf("%d %d", &n, &c);

        for (int i = 0; i < c; i++) {
            scanf("%d", &op);
            if (op == 0) {
                scanf("%d %d %lld", &p, &q, &v);
                update(1, 1, n, p, q, v);
            }
            else {
                scanf("%d %d", &p, &q);
                printf("%lld\n", query(1, 1, n, p, q));
            }
        }
    }

    return 0;
}
