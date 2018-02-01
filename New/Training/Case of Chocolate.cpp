#include <bits/stdc++.h>

using namespace std;

#define N 200200

int n, q;

struct query {
    int x, y;
    char op;
} queries[N];

int val[2 * N + 2];
set < int > nums;
map < int, int > ind;
set < vector < int > > calc;

struct Node {
    int val, acum;

    void atualize(int x) {
        val = max(val, x);
        acum = max(acum, x);
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
        val = max(left.val, right.val);
    }

} seg[2][8*N + 8];

void update(int t, int id, int ini, int fim, int start, int end, int val) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[t][id].atualize(val);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[t][id].shift(seg[t][2*id], seg[t][2*id+1]);

    update(t, 2*id, ini, meio, start, end, val);
    update(t, 2*id+1, meio+1, fim, start, end, val);

    seg[t][id]._merge(seg[t][2*id], seg[t][2*id+1]);
}

int query(int t, int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[t][id].val;

    int meio = (ini + fim) / 2;
    seg[t][id].shift(seg[t][2*id], seg[t][2*id+1]);

    return query(t, 2*id, ini, meio, start, end) + query(t, 2*id+1, meio+1, fim, start, end);
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d %c", &queries[i].x, &queries[i].y, &queries[i].op);
        nums.insert(queries[i].x);
        nums.insert(queries[i].y);
    }
    nums.insert(0);

    int cont = 1;
    for (auto v : nums) {
        val[cont] = v;
        ind[v] = cont++;
    }

    for (int i = 0; i < q; i++) {
        if (calc.count(vector <int>({queries[i].x, queries[i].y, queries[i].op}))) {
            printf("0\n");
            continue;
        }
        calc.insert(vector <int>({queries[i].x, queries[i].y, queries[i].op}));

        if (queries[i].op == 'U') {
            int x = query(0, 1, 1, 2*N, ind[queries[i].x], ind[queries[i].x]);
            printf("%d\n", queries[i].y - x);
            update(1, 1, 1, 2*N, ind[x], ind[queries[i].y], queries[i].x);
        }
        else {
            int x = query(1, 1, 1, 2*N, ind[queries[i].y], ind[queries[i].y]);
            printf("%d\n", queries[i].x - x);
            update(0, 1, 1, 2*N, ind[x], ind[queries[i].x], queries[i].y);
        }
    }

    return 0;
}
