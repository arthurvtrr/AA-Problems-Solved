#include <bits/stdc++.h>

using namespace std;

#define N 500500

int n, q, t, x, y, z, seg[4*N], nums[N];

int gcd(int a, int b) {
    return b == 0? a : gcd(b, a % b);
}

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = nums[ini];
        return;
    }
    int meio = (ini + fim) / 2;

    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);

    seg[id] = gcd(seg[2*id], seg[2*id+1]);
}

void update(int id, int ini, int fim, int pos, int val) {
    if (ini == fim) {
        seg[id] = val;
        return;
    }
    int meio = (ini + fim) / 2;

    if (pos <= meio) update(2*id, ini, meio, pos, val);
    else update(2*id+1, meio+1, fim, pos, val);

    seg[id] = gcd(seg[2*id], seg[2*id+1]);
}

bool finish;

int ffirst(int id, int ini, int fim, int start, int end) {
    if (finish) return y+1;
    if (start > fim || end < ini) return y+1;

    if (ini == fim && (seg[id] % z)) {
        finish = true;
        return ini;
    }
    if (ini == fim) return y+1;

    int meio = (ini + fim) / 2;

    if (ini >= start && fim <= end) {
        if (seg[2*id] % z) return ffirst(2*id, ini, meio, start, end);
        if (seg[2*id+1] % z) return ffirst(2*id+1, meio+1, fim, start, end);
        return y+1;
    }

	int l = ffirst(2*id, ini, meio, start, end);
	int r = ffirst(2*id+1, meio+1, fim, start, end);

	return min(l, r);
}

int flast(int id, int ini, int fim, int start, int end) {
    if (finish) return x-1;
    if (start > fim || end < ini) return x-1;

    if (ini == fim && (seg[id] % z)) {
        finish = true;
        return ini;
    }
    if (ini == fim) return x-1;

    int meio = (ini + fim) / 2;

    if (ini >= start && fim <= end) {
        if (seg[2*id+1] % z) return flast(2*id+1, meio+1, fim, start, end);
        if (seg[2*id] % z) return flast(2*id, ini, meio, start, end);
        return x-1;
    }

    int l = flast(2*id+1, meio+1, fim, start, end);
    int r = flast(2*id, ini, meio, start, end);

    return max(l, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    build(1, 1, n);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d %d", &x, &y, &z);

            if (y - x == 0) printf("YES\n");
            else {
                finish = false;
                int a = ffirst(1, 1, n, x, y);
                finish = false;
                int b = flast(1, 1, n, x, y);

                if (a - x + y - b >= y - x) printf("YES\n");
                else printf("NO\n");
            }
        }
        else {
            scanf("%d %d", &x, &y);
            update(1, 1, n, x, y);
        }
    }

    return 0;
}
