#include <stdio.h>
#include <algorithm>

using namespace std;

struct Node {
    int vals[3];
    int aux[3];
    int acum;

    void shift(Node& left, Node& right) {
        left.acum += acum;
        right.acum += acum;
        aux[acum % 3] = vals[0];
        aux[(acum + 1) % 3] = vals[1];
        aux[(acum + 2) % 3] = vals[2];
        vals[0] = aux[0];
        vals[1] = aux[1];
        vals[2] = aux[2];
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
        vals[0] = left.vals[0] + right.vals[0];
        vals[1] = left.vals[1] + right.vals[1];
        vals[2] = left.vals[2] + right.vals[2];
    }

    Node zero() {
        Node x;
        x.vals[0] = x.vals[1] = x.vals[2] = x.acum = 0;
        return x;
    }

} seg[800800];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].vals[0] = 1;
        return;
    }

    int meio = (ini + fim) / 2;
    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[id].acum++;
        seg[id].shift(seg[2*id], seg[2*id+1]);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    update(2*id, ini, meio, start, end);
    update(2*id+1, meio+1, fim, start, end);

    seg[2*id].shift(seg[4*id], seg[4*id+1]);
    seg[2*id+1].shift(seg[4*id + 2], seg[4*id + 3]);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

Node query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini) {
        Node x;
        return x.zero();
    }
    if (ini >= start && fim <= end) {
        seg[id].shift(seg[2*id], seg[2*id+1]);
        return seg[id];
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    Node left = query(2*id, ini, meio, start, end);
    Node right = query(2*id+1, meio+1, fim, start, end);
    left.shift(seg[4*id], seg[4*id+1]);
    right.shift(seg[4*id + 2], seg[4*id + 3]);

    Node result = result.zero();
    result._merge(left, right);
    return result;
}

int main() {
    int n, m, a, b;
    char op[3];

    while (scanf("%d", &n) != EOF) {
        scanf("%d", &m);

        for (int i = 0; i < 800800; i++) {
            seg[i].vals[0] = seg[i].vals[1] = seg[i].vals[2] = seg[i].acum = 0;
        }

        build(1, 1, n);

        for (int i = 0; i < m; i++) {
            scanf("%s", op);
            if (op[0] == 'C') {
                scanf("%d %d", &a, &b);
                Node result = query(1, 1, n, a, b);
                printf("%d %d %d\n", result.vals[0], result.vals[1], result.vals[2]);
            }
            else {
                scanf("%d %d", &a, &b);
                update(1, 1, n, a, b);
            }
        }
        printf("\n");
    }

    return 0;
}
