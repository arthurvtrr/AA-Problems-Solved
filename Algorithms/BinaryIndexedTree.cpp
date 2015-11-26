#include <stdio.h>

using namespace std;

int nums[66000], bit[66000];

void update(int pos, int x, int n) {
    while (pos <= n) {
        bit[pos] += x;
        pos += pos & -pos;
    }
}

// return the sum of elements from index 1 to index pos
int query(int pos) {
    int sum = 0;
    while (pos) {
        sum += bit[pos];
        pos -= pos & -pos;
    }
    return sum;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        // building the BIT
        update(i, nums[i], n);
    }
    return 0;
}
