#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

#define N 100100

struct Node {
    int val;
    int acum = 10000000;

    void atualize(int x) {
        val = min(val, x);
        acum = min(acum, x);
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 10000000;
    }

    void _merge(Node& left, Node& right) {
        val = min(left.val, right.val);
    }

} seg[4*N];

int n, m, nums[100100], maxi[100100];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].val = maxi[ini];
        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int start, int end, int val) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[id].atualize(val);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    update(2*id, ini, meio, start, end, val);
    update(2*id+1, meio+1, fim, start, end, val);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

int query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id].val;

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    return query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end);
}

#define pii pair < int, int >

pii subs[100100];

int main() {
    scanf("%d %d", &n, &m);

    int mini = 10000000;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &subs[i].first, &subs[i].second);
        mini = min(mini, subs[i].second - subs[i].first + 1);
    }

    for (int i = 1; i <= n; i++)
        maxi[i] = 100000;

    build(1, 1, n);

    for (int i = 0; i < m; i++)
        update(1, 1, n, subs[i].first, subs[i].second, subs[i].second - subs[i].first);

    printf("%d\n", mini);
    int aux = 0;
    for (int i = 0; i < n; i++) {
        if (query(1, 1, n, i+1, i+1) < aux)
            aux = 0;
        nums[i] = aux++;
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", nums[i]);
    }
    printf("\n");

    return 0;
}
