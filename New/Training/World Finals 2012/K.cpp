#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, heights[55][55];
vector < int > ord;
set < pii > found, need;

int main() {
    int t = 1;
    while (scanf("%d", &n) != EOF) {
        ord.clear();
        found.clear();
        need.clear();

        for (int i = 0; i < n; i++) {
            scanf("%d", &heights[i][0]);
            for (int j = 1; j <= heights[i][0]; j++) {
                scanf("%d", &heights[i][j]);
                ord.push_back(heights[i][j]);
            }
        }
        sort(ord.begin(), ord.end());
        for (int i = 1; i < ord.size(); i++)
            if (ord[i-1] != ord[i])
                need.insert(pii(ord[i-1], ord[i]));

        int moves = n-1;
        for (int i = 0; i < n; i++)
            for (int j = 1; j < heights[i][0]; j++)
                if (heights[i][j] != heights[i][j+1]) {
                    if (!need.count(pii(heights[i][j], heights[i][j+1]))) moves += 2;
                    else if (found.count(pii(heights[i][j], heights[i][j+1]))) moves += 2;
                    else found.insert(pii(heights[i][j], heights[i][j+1]));
                }
        printf("Case %d: %d\n", t++, moves);
    }

    return 0;
}
