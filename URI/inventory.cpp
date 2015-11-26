#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

struct num {
    int pos;
    int v;
} nums[110000];

bool f[110000];

int main() {
    int n, x;
    scanf("%d", &n);
    vector < num > tochange;

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        nums[i].pos = i;
        nums[i].v = x;
        if (f[x] || x > n)
            tochange.push_back(nums[i]);
        f[x]++;
    }

    int c = 0;
    for (int i = 1; i <= n; i++) {
        if (!f[i]) {
            nums[tochange[c].pos].v = i;
            c++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", nums[i].v);
    }
    printf("\n");

    return 0;
}
