#include <stdio.h>
#include <algorithm>

using namespace std;

#define N 110000

int seg[4*N];

//array with initial numbers
int nums[N];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = nums[ini];
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

	return query(2*id, ini, meio, start, meio) + query(2*id+1, meio+1, fim, meio+1, end);
}
