#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
    int c, n;
    int olives[11000];
    while(scanf("%d %d", &c, &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%d", &olives[i]);
        olives[n] = olives[0] + c;
        olives[n+1] = olives[1] + c;

        int maxd = 1, mind = 1000000;
        for (int i = 1; i < n+1; i++) {
            if (olives[i] - olives[i-1] > maxd) maxd = olives[i] - olives[i-1];
            if (olives[i+1] - olives[i-1] < mind) mind = olives[i+1] - olives[i-1];
        }
        if (maxd < 2*mind) printf("S\n");
        else printf("N\n");
    }
    return 0;
}
