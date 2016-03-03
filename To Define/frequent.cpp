#include <stdio.h>
#include <math.h>
#include <map>

using namespace std;

struct Node {
	map < int, int > freq;

	void assignLeaf(int x) {
		freq[x] = 1;
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

int main() {
    int n, q;
    while(1) {
        scanf("%d", &n);
        if (n == 0) break;
        scanf("%d", &q);

        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        build(1, 1, n);

        int x, y;
        for (int i = 0; i < q; i++) {
            scanf("%d %d", &x, &y);
            Node s = query(1, 1, n, x, y);
            printf("%d\n", s.getValue());
        }
    }
    return 0;
}

