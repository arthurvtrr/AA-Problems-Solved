#include <bits/stdc++.h>

using namespace std;

#define N 110000

struct Node {
    double val, acum[2], siz;

    void atualize(double x, int t) {
		if (t == 0) {
			val *= x;
			acum[0] *= x; acum[1] *= x;
		}
		else {
			val += x * siz;
			acum[1] += x;
		}
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum[0], 0); left.atualize(acum[1], 1);
        right.atualize(acum[0], 0); right.atualize(acum[1], 1);
        acum[0] = 1.0; acum[1] = 0.0;
    }

    void _merge(Node& left, Node& right) {
		val = left.val + right.val;
    }

} seg[4*N];

int n, q, t, a, b, c, d, nums[N];

void build(int id, int ini, int fim) {
	seg[id].siz = fim - ini + 1;
	seg[id].acum[0] = 1.0; seg[id].acum[1] = 0.0;

    if (ini == fim) {
        seg[id].val = nums[ini];
        return;
    }

    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int start, int end, double val, int t) {
    if (start > fim || end < ini)
        return;
    if (ini >= start && fim <= end) {
        seg[id].atualize(val, t);
        return;
    }

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    update(2*id, ini, meio, start, end, val, t);
    update(2*id+1, meio+1, fim, start, end, val, t);

    seg[id]._merge(seg[2*id], seg[2*id+1]);
}

double query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return 0;
    if (ini >= start && fim <= end)
        return seg[id].val;

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    return query(2*id, ini, meio, start, end) + query(2*id+1, meio+1, fim, start, end);
}

int main() {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &nums[i]);

	build(1, 1, n);

	for (int i = 0; i < q; i++) {
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			double x = query(1, 1, n, a, b) / (b - a + 1), y = query(1, 1, n, c, d) / (d - c + 1);
			double aux = b - a;
			aux /= b - a + 1;
			update(1, 1, n, a, b, aux, 0);
			aux = y;
			aux /= b - a + 1;
			update(1, 1, n, a, b, aux, 1);

			aux = d - c;
			aux /= d - c + 1;
			update(1, 1, n, c, d, aux, 0);
			aux = x;
			aux /= d - c + 1;
			update(1, 1, n, c, d, aux, 1);
		}
		else {
			scanf("%d %d", &a, &b);
			printf("%.7f\n", query(1, 1, n, a, b));
		}
	}

	return 0;
}

