#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace std;

struct Node {
	int max1, max2;

	void assignLeaf(int x) {
		max1 = x;
		max2 = 0;
	}

	void merge(Node& left, Node& right) {
		max1 = fmax(fmax(left.max1, right.max1), fmax(fmin(left.max1, right.max1), fmax(left.max2, right.max2)));
        max2 = fmin(fmax(left.max1, right.max1), fmax(fmin(left.max1, right.max1), fmax(left.max2, right.max2)));
	}

	int getValue() {
		return max1 + max2;
	}
};

int a[110000];
Node seg[440000];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id].assignLeaf(a[ini]);
        return;
    }
    int meio = (ini + fim) / 2;
    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);
    seg[id].merge(seg[2*id], seg[2*id+1]);
}

Node query(int id, int ini, int fim, int start, int end) {
    if (ini >= start && fim <= end) return seg[id];

    int meio = (ini + fim) / 2;

    if (start > meio) return query(2*id+1, meio+1, fim, start, end);
    if (end <= meio) return query(2*id, ini, meio, start, end);

    Node leftResult = query(2*id, ini, meio, start, meio);
    Node rightResult = query(2*id+1, meio+1, fim, meio+1, end);
	Node result;
	result.merge(leftResult, rightResult);
	return result;
}

void update(int id, int ini, int fim, int index, int x) {
    if (ini == fim) {
        seg[id].assignLeaf(x);
        return;
    }

    int meio = (ini + fim) / 2;

    if (index <= meio) update(2*id, ini, meio, index, x);
    else update(2*id+1, meio+1, fim, index, x);

    seg[id].merge(seg[2*id], seg[2*id+1]);
}

int main() {
    int n, q;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    build(1, 1, n);

    scanf("%d", &q);

    char a;
    int x, y;
    for (int i = 0; i < q; i++) {
        cin >> a >> x >> y;
        if (a == 'U') update(1, 1, n, x, y);
        else {
            Node s = query(1, 1, n, x, y);
            printf("%d\n", s.getValue());
        }
    }

    return 0;
}

