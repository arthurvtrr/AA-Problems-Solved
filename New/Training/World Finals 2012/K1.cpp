#include <bits/stdc++.h>

using namespace std;

#define pii pair < int, int >

int n, heights[55][55];
vector < int > ord;
set < pii > found, need;
set < int > app;
map < int, int > num, cut;

int main() {
    int t = 1;
    while (scanf("%d", &n) != EOF) {
        ord.clear();
        found.clear();
        need.clear();
        num.clear();
        cut.clear();

        for (int i = 0; i < n; i++) {
            scanf("%d", &heights[i][0]);
            app.clear();
            for (int j = 1; j <= heights[i][0]; j++) {
                scanf("%d", &heights[i][j]);
                ord.push_back(heights[i][j]);
                app.insert(heights[i][j]);
            }
            for (auto v : app)
                num[v]++;
        }

        sort(ord.begin(), ord.end());
        for (int i = 1; i < ord.size(); i++)
            if (ord[i-1] != ord[i])
                need.insert(pii(ord[i-1], ord[i]));

        int moves = n-1;
        for (int i = 0; i < n; i++) {
            bool fst = false, lst = false;

            for (int j = 1; j < heights[i][0]; j++)
                if (heights[i][j] != heights[i][j+1]) {
                    if (!need.count(pii(heights[i][j], heights[i][j+1]))) {
                        moves += 2;
                        cut[heights[i][j]]++;
                        cut[heights[i][j+1]]++;
                        if (j == 1) fst = true;
                        if (j == heights[i][0]-1) lst = true;
                    }
                    else if (found.count(pii(heights[i][j], heights[i][j+1]))) {
                        moves += 2;
                        cut[heights[i][j]]++;
                        cut[heights[i][j+1]]++;
                        if (j == 1) fst = true;
                        if (j == heights[i][0]-1) lst = true;
                    }
                    else found.insert(pii(heights[i][j], heights[i][j+1]));
                }
            if (!fst) cut[heights[i][1]]++;
            if (heights[i][1] != heights[i][heights[i][0]] && !lst) cut[heights[i][heights[i][0]]]++;
        }

        for (auto v : num)
            if (v.second > 1 && v.second > cut[v.first])
                moves += 2;

        printf("Case %d: %d\n", t++, moves);
    }

    return 0;
}
