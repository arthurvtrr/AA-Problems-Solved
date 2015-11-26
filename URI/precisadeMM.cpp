#include <stdio.h>
#include <algorithm>

using namespace std;

int nums[110000], bit[110000];

void update(int pos, int x, int n) {
    pos++;
    while (pos <= n) {
        bit[pos] += x;
        pos += pos & -pos;
    }
}

int query(int pos) {
    pos++;
    int sum = 0;
    while (pos) {
        sum += bit[pos];
        pos -= pos & -pos;
    }
    return sum;
}

int main() {
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        update(i, nums[i], n);
    }

    char op[3];
    while(scanf("%s %d", op, &x) != EOF) {
        if (op[0] == 'a') update(x-1, -nums[x-1], n);
        else printf("%d\n", query(x-2));
    }
    return 0;
}
