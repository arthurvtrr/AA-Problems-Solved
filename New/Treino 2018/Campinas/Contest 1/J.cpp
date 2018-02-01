#include <bits/stdc++.h>

using namespace std;

int n, p;

#define N 1000100

int seg[4*N];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = 1;
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
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

	return query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end);
}

int atual, done;

void segs(int id, int ini, int fim, int lft) {
    if (done) return;

    if (ini == fim) {
        atual = ini; done = 1;
        return;
    }

    int meio = (ini + fim) / 2;

    if (seg[2*id] >= lft) segs(2*id, ini, meio, lft);
    else segs(2*id+1, meio+1, fim, lft-seg[2*id]);
}

int main() {
    scanf("%d %d", &n, &p);
    build(1, 1, n);

    atual = ((p-1) % n) + 1;
    if (n > 1) update(1, 1, n, atual, 0);

    for (int i = 1; i < n-1; i++) {
        int x = query(1, 1, n, 1, atual);

        done = 0;
        if (n-i-x >= ((p-1) % (n-i)) + 1) segs(1, 1, n, x + ((p-1) % (n-i)) + 1);
        else segs(1, 1, n, ((p-1) % (n-i)) + 1 - (n-i-x));

        update(1, 1, n, atual, 0);
    }

    for (int i = 1; i <= n; i++)
        if (query(1, 1, n, 1, i) == 1) {
            printf("%d\n", i);
            break;
        }

    return 0;
}
