#include <bits/stdc++.h>

using namespace std;

string s;
int m, x, y;

#define N 1100000

struct Node {
	int ans, op, cl;
	Node() { ans = op = cl = 0; }
} seg[4*N];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        if (s[ini-1] == '(') seg[id].op = 1;
        else seg[id].cl = 1;
        return;
    }
    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id].ans = seg[2*id].ans + seg[2*id+1].ans;
    seg[id].ans += 2 * min(seg[2*id].op, seg[2*id+1].cl);
    seg[id].op = seg[2*id].op + seg[2*id+1].op - min(seg[2*id].op, seg[2*id+1].cl);
    seg[id].cl = seg[2*id].cl + seg[2*id+1].cl - min(seg[2*id].op, seg[2*id+1].cl);
}

Node query(int id, int ini, int fim, int start, int end) {
    if (start > fim || end < ini)
        return Node();
    if (ini >= start && fim <= end)
        return seg[id];

    int meio = (ini + fim) / 2;

    Node l = query(2*id, ini, meio, start, end);
    Node r = query(2*id+1, meio+1, fim, start, end);
    Node ret = Node();
    ret.ans = l.ans + r.ans;
    ret.ans += 2 * min(l.op, r.cl);
    ret.op = l.op + r.op - min(l.op, r.cl);
    ret.cl = l.cl + r.cl - min(l.op, r.cl);

	return ret;
}

int main() {
	cin >> s;
	build(1, 1, s.size());

	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		printf("%d\n", query(1, 1, s.size(), x, y).ans);
	}
	return 0;
}
