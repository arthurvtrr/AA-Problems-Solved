#include <stdio.h>
#include <algorithm>

using namespace std;

struct Node {
    int quant0[25], quant1[25];
    int acum = 0;

    void shift(Node& left, Node& right) {
        left.acum ^= acum;
        right.acum ^= acum;

        int ind = 0, aux;
        while (acum) {
            if (acum & 1) {
                aux = quant0[ind];
                quant0[ind] = quant1[ind];
                quant1[ind] = aux;
            }
            ind++;
            acum >>= 1;
        }
    }

    void _merge(Node& left, Node& right) {
        for (int i = 0; i < 25; i++) {
            quant1[i] = left.quant1[i] + right.quant1[i];
            quant0[i] = left.quant0[i] + right.quant0[i];
        }
    }

    long long calc() {
        long long val = 0;
        for (int i = 0; i < 25; i++)
            val += pow(2, i) * quant1[i];
        return val;
    }

} seg[800800];

int nums[110000];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        int ind = 0;
        while (nums[ini]) {
            if (nums[ini] & 1) {
                seg[id].quant1[ind] = 1;
                seg[id].quant0[ind] = 0;
            }
            ind++;
            nums[ini] >>= 1;
        }
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
        seg[id].acum ^= val;
        seg[id].shift(seg[2*id], seg[2*id+1]);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    update(2*id, ini, meio, start, end, val);
    update(2*id+1, meio+1, fim, start, end, val);

    seg[2*id].shift(seg[4*id], seg[4*id+1]);
    seg[2*id+1].shift(seg[4*id + 2], seg[4*id + 3]);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

long long query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end) {
        seg[id].shift(seg[2*id], seg[2*id+1]);
        return seg[id].calc();
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    return query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end);
}

int main() {
    for (int i = 0; i < 800800; i++)
        for (int j = 0; j < 25; j++) {
            seg[i].quant0[j] = 1;
            seg[i].quant1[j] = 0;
        }

    int n, m, op, l, r, x;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    build(1, 1, n);

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        scanf("%d", &op);
        if (op == 2) {
            scanf("%d %d %d", &l, &r, &x);
            update(1, 1, n, l, r, x);
        }
        else {
            scanf("%d %d", &l, &r);
            printf("%lld\n", query(1, 1, n, l, r));
        }
    }

    return 0;
}
