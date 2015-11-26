#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int n, g, x, y;
    while(scanf("%d %d", &n, &g) != EOF) {
        int sol = 0;
        vector < int > loses;
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x, &y);
            if (x > y) sol += 3;
            else if (x == y && g > 0) {
                sol += 3;
                g--;
            }
            else if (x == y) sol++;
            else loses.push_back(y-x);
        }
        sort(loses.begin(), loses.end());
        for (int i = 0; i < loses.size(); i++) {
            if (g > loses[i]) {
                g -= loses[i] + 1;
                sol += 3;
            }
            else if (g == loses[i]) {
                g -= loses[i];
                sol++;
                break;
            }
            else break;
        }
        printf("%d\n", sol);
    }
    return 0;
}
