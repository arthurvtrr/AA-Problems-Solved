#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

struct skycp {
    int ind;
    int height;
} skycps[1001000];

bool cmp(skycp a, skycp b) {
    return a.height < b.height;
}

int t, n, d, x;
bool flooded[1001000];

int main() {
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d", &n, &d);

        for (int i = 0; i < n; i++) {
            scanf("%d", &skycps[i].height);
            skycps[i].ind = i+1;
        }

        sort(skycps, skycps+n, cmp);

        for (int i = 0; i < 1001000; i++)
            flooded[i] = false;
        flooded[0] = flooded[n+1] = true;

        int regions = 1, day = 0, pos = 0;
        for (int i = 0; i < d; i++) {
            scanf("%d", &x);
            while (day != x) {
                day++;
                while (skycps[pos].height == day) {
                    flooded[skycps[pos].ind] = true;
                    if (flooded[skycps[pos].ind-1] == flooded[skycps[pos].ind+1] && flooded[skycps[pos].ind-1]) {
                        regions--;
                    }
                    else if (flooded[skycps[pos].ind-1] == flooded[skycps[pos].ind+1]) {
                        regions++;
                    }
                    pos++;
                }
            }
            if (i > 0) printf(" ");
            printf("%d", regions);
        }
        printf("\n");
    }
    return 0;
}
