#include <stdio.h>
#include <algorithm>

using namespace std;

#define N 110000

int n, nums[N], bit[N];

void update(int pos, int x) {
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
