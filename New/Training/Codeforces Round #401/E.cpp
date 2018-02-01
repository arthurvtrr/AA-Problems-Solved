#include <bits/stdc++.h>

using namespace std;

#define N 100100

int n;

struct ring {
    long long a, b, h;
} rings[N];

bool cmp(ring a, ring b) {
    if (a.b == b.b)
        return a.a > b.a;
    return a.b > b.b;
}

long long seg[8 * N];

void update(int id, int ini, int fim, int pos, long long val) {
    if (ini == fim) {
        seg[id] = val;
        return;
    }
    int meio = (ini + fim) / 2;

    if (pos <= meio) update(2*id, ini, meio, pos, val);
    else update(2*id+1, meio+1, fim, pos, val);

    seg[id] = max(seg[2*id], seg[2*id+1]);
}

long long query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

	return max(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

set < long long > compress;
map < long long, int > val;

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &rings[i].a, &rings[i].b, &rings[i].h);
        compress.insert(rings[i].a);
        compress.insert(rings[i].b);
    }

    int cont = 2;
    for (set < long long >::iterator it = compress.begin(); it != compress.end(); it++)
        val[*it] = cont++;

    for (int i = 0; i < n; i++) {
        rings[i].a = val[rings[i].a];
        rings[i].b = val[rings[i].b];
    }

    sort(rings, rings+n, cmp);

    for (int i = 0; i < n; i++) {
        long long x = query(1, 1, 2*N, 1, rings[i].b-1);
        update(1, 1, 2*N, rings[i].a, x + rings[i].h);
    }

    printf("%lld\n", seg[1]);

    return 0;
}
