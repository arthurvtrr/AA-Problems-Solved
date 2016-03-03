#include <stdio.h>
#include <math.h>

using namespace std;

struct Node {
    int maxi;
    long long sum;
    int ind;
};

int nums[110000];
Node seg[440000];

Node merge_(Node a, Node b) {
    Node c = {fmax(a.maxi, b.maxi), a.sum + b.sum, a.maxi > b.maxi? a.ind : b.ind};
    return c;
}

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = (Node) {nums[ini], nums[ini], ini};
        return;
    }
    int meio = (ini + fim) / 2;
    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);
    seg[id] = merge_(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int pos, int val) {
    if (ini > pos || fim < pos) return;
    if (ini == fim) {
        seg[id] = (Node) {val, val, pos};
        return;
    }
    int meio = (ini + fim) / 2;
    update(2*id, ini, meio, pos, val);
    update(2*id+1, meio+1, fim, pos, val);
    seg[id] = merge_(seg[2*id], seg[2*id+1]);
}

Node query(int id, int ini, int fim, int start, int end) {
    if (end < ini || start > fim) return (Node) {0, 0, 0};
    if (ini >= start && fim <= end) return seg[id];
    int meio = (ini + fim) / 2;
    return merge_(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

int main() {
    int n, m, t, x, y, z;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    build(1, 1, n);

    for (int i = 0; i < m; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &x, &y);
            Node aux = query(1, 1, n, x, y);
            printf("%I64d\n", aux.sum);
        }
        else if (t == 2) {
            scanf("%d %d %d", &x, &y, &z);
            while (true) {
                Node aux = query(1, 1, n, x, y);
                if (aux.maxi < z) break;
                update(1, 1, n, aux.ind, aux.maxi % z);
            }
        }
        else {
            scanf("%d %d", &x, &y);
            update(1, 1, n, x, y);
        }
    }

    return 0;
}
