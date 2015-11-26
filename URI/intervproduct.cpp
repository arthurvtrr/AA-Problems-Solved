#include <stdio.h>
#include <algorithm>

using namespace std;

int nums[110000], seg[440000];

void build(int id, int ini, int fim) {
    if (ini == fim) {
        seg[id] = nums[ini];
        return;
    }
    int meio = (ini + fim) / 2;
    build(2*id, ini, meio);
    build(2*id+1, meio+1, fim);
    seg[id] = seg[2*id] * seg[2*id+1];
}

void update(int id, int ini, int fim, int pos, int x) {
    if (ini == fim) {
        seg[id] = x;
        return;
    }

    int meio = (ini + fim) / 2;
    if (pos <= meio) update(2*id, ini, meio, pos, x);
    else update(2*id+1, meio+1, fim, pos, x);
    seg[id] = seg[2*id] * seg[2*id+1];
}

int query(int id, int ini, int fim, int start, int end) {
    if (ini > end || fim < start) return 1;
    if (ini >= start && fim <= end) return seg[id];

    int meio = (ini + fim) / 2;
    return query(2*id, ini, meio, start, end) * query(2*id+1, meio+1, fim, start, end);
}

int main() {
    int n, k, x, y;

    while (scanf("%d %d", &n, &k) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &nums[i]);
            if (nums[i] > 0) nums[i] = 1;
            else if (nums[i] < 0) nums[i] = -1;
        }

        build(1, 1, n);

        char op[3];
        for (int i = 0; i < k; i++) {
            scanf("%s %d %d", op, &x, &y);
            if (op[0] == 'C') {
                if (y > 0) y = 1;
                else if (y < 0) y = -1;
                update(1, 1, n, x, y);
            }
            else {
                int sol = query(1, 1, n, x, y);
                if (sol > 0) printf("+");
                else if (sol < 0) printf("-");
                else printf("0");
            }
        }
        printf("\n");
    }
    return 0;
}
