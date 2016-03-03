#include <stdio.h>
#include <math.h>

using namespace std;

struct Node {
	int leftMaxSum, rightMaxSum, maxSum, sum;

	void assignLeaf(int x) {
		leftMaxSum = rightMaxSum = maxSum = sum = x;
	}

	void merge(Node& left, Node& right) {
		sum = left.sum + right.sum;
		leftMaxSum = fmax(left.leftMaxSum, left.sum + right.leftMaxSum);
		rightMaxSum = fmax(right.rightMaxSum, right.sum + left.rightMaxSum);
		maxSum = fmax(leftMaxSum, fmax(rightMaxSum, fmax(left.maxSum, fmax(right.maxSum, left.rightMaxSum + right.leftMaxSum))));
	}

	int getValue() {
		return maxSum;
	}
};

int a[55000];
Node seg[200000];

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
    int n, m;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    build(1, 1, n);

    scanf("%d", &m);

    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        Node s = query(1, 1, n, x, y);
        printf("%d\n", s.getValue());
    }

    return 0;
}
