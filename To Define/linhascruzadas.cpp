#include <stdio.h>

using namespace std;

int nums[66000], bit[66000];

void update(int pos, int x, int n) {
    while (pos <= n) {
        bit[pos] += x;
        pos += pos & -pos;
    }
}

int query(int pos) {
    int sum = 0;
    while (pos) {
        sum += bit[pos];
        pos -= pos & -pos;
    }
    return sum;
}

int main() {
    int n, sol = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        sol += query(n) - query(nums[i]);
        update(nums[i], 1, n);
    }
    printf("%d\n", sol);
    return 0;
}
