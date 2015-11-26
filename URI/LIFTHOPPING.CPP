#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n, k, x, y;
    char c;
    while (scanf("%d %d", &n, &k) != EOF) {
        vector < pair < pair < int, int >, int > > elev[110];
        int dists[n+10];

        for (int i = 1; i <= n; i++)
            scanf("%d", &dists[i]);

        for (int i = 1; i <= n; i++) {
            scanf("%d", &x);
            while (scanf("%d", &y) && y > x) {
                elev[x].push_back(make_pair(make_pair(y, (y - x) * dists[i]), i));
                elev[y].push_back(make_pair(make_pair(x, (y - x) * dists[i]), i));
                x = y;
            }
            printf("a");
        }
    }

    return 0;
}
