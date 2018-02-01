#include <bits/stdc++.h>

using namespace std;

#define ll long long

int t, n, nums[100100];
int bit[1000100];

void update(int pos, int val) {
    while (pos < 1000100) {
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
    scanf("%d", &t);
    while (t--) {
        memset(bit, 0, sizeof bit);

        scanf("%d", &n);

        ll aux = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
            aux += i - query(nums[i]);
            update(nums[i], 1);
        }

        for (int i = 0; i < n; i++) {
            int x = query(nums[i]-1);
            aux -= x; aux += n-1-x;
            if (i) printf(" ");
            printf("%lld", aux);
        }
        printf("\n");
    }

    return 0;
}
