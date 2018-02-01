#include <bits/stdc++.h>

using namespace std;

#define INF 10000000

int n, x, bit[300300];
string op;

void update(int pos, int val) {
    while (pos < 300300) {
        bit[pos] += val;
        pos += pos & -pos;
    }
}

int query(int pos) {
    int ret = 0;
    while (pos) {
        ret += bit[pos];
        pos -= pos & -pos;
    }
    return ret;
}

int main() {
    scanf("%d", &n);

    int ans = 0, lft = 0, lst = INF, nxt = 1;

    for (int i = 0; i < 2*n; i++) {
        cin >> op;
        if (op == "add") {
            scanf("%d", &x);
            lft++;
            if (query(x) != 0) lst = lft;
            update(x, 1);
        }
        else {
            if (lst == lft) { ans++; lst = INF; }
            update(nxt, -1);
            nxt++; lft--;
        }
    }
    printf("%d\n", ans);

    return 0;
}

