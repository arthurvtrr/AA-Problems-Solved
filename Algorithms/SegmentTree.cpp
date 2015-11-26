#include <stdio.h>
#include <algorithm>

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
    seg[id] = seg[2*id] + seg[2*id+1];
}

int query(int id, int ini, int fim, int start, int end) {
    if (ini >= start && fim <= end) return seg[id];

    int meio = (ini + fim) / 2;

    if (start > meio) return query(2*id+1, meio+1, fim, start, end);
    if (end <= meio) return query(2*id, ini, meio, start, end);

	return query(2*id, ini, meio, start, meio) + query(2*id+1, meio+1, fim, meio+1, end);
}

void update(int id, int ini, int fim, int index, int x) {
    if (ini == fim) {
        seg[id] = x;
        return;
    }
    int meio = (ini + fim) / 2;

    if (index <= meio) update(2*id, ini, meio, index, x);
    else update(2*id+1, meio+1, fim, index, x);

    seg[id] = seg[2*id] + seg[2*id+1];
}
