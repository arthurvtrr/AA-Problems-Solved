#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n;
pii mummy[100100];

struct event {
	int x, y1, y2, type;
};

bool cmp(event a, event b) {
	if (a.x == b.x)
		return a.type < b.type;
	return a.x < b.x;
}

#define N 4004000

struct Node {
    int acum, val;

    void atualize(int x) {
		val = val + x;
		acum = acum + x;
    }

    void shift(Node& left, Node& right) {
        left.atualize(acum);
        right.atualize(acum);
        acum = 0;
    }

    void _merge(Node& left, Node& right) {
		val = min(left.val, right.val);
    }
} seg[4*N];

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
        return 10000000;
    if (ini >= start && fim <= end)
		return seg[id].val;

    int meio = (ini + fim) / 2;
    seg[id].shift(seg[2*id], seg[2*id+1]);

    return min(query(2*id, ini, meio, start, end), query(2*id+1, meio+1, fim, start, end));
}

vector < event > events;

bool valid(int t) {
	events.clear();
	for (int i = 0; i < n; i++) {
		events.push_back((event) {mummy[i].first - t, mummy[i].second - t, mummy[i].second + t, 1});
		events.push_back((event) {mummy[i].first + t, mummy[i].second - t, mummy[i].second + t, -1});
	}
	events.push_back((event) {-t, -t, t, 0});
	events.push_back((event) {t, -t, t, 0});

	sort(events.begin(), events.end(), cmp);

	bool possible = false;
	for (int i = 0; i < 2*n+2; i++) {
		update(1, 1, N-1, events[i].y1 + N/2, events[i].y2 + N/2, events[i].type);
		if (events[i].x >= -t && events[i].x <= t) {
			if ((events[i+1].x != events[i].x || i == 2*n+1) && query(1, 1, N-1, -t + N/2, t + N/2) == 0)
				possible = true;
		}
	}

	return possible;
}

int main() {
	int t = 1;
	while (1) {
		scanf("%d", &n);
		if (n == -1) break;

		for (int i = 0; i < n; i++)
			scanf("%d %d", &mummy[i].first, &mummy[i].second);

		int ini = 0, fim = 1001000;
		while (ini <= fim) {
			int meio = (ini + fim) / 2;
			if (valid(meio)) ini = meio+1;
			else fim = meio-1;
		}

		if (fim == 1001000) printf("Case %d: never\n", t++);
		else printf("Case %d: %d\n", t++, max(1, fim+1));
	}

	return 0;
}
