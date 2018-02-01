#include <bits/stdc++.h>

using namespace std;

int n, q, l, r, nums[1550];
int bit[1550];

void update(int pos, int val) {
    while (pos < 1550) {
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

    int inv = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        inv += i - query(nums[i]);
        update(nums[i], 1);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d", &l, &r);

        int siz = r - l + 1;
        inv += siz / 2;
        if (inv % 2) printf("odd\n");
        else printf("even\n");
    }

    return 0;
}
