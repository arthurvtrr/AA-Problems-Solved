#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int t, n, k;

struct box {
    int vs;
    int cs;
} boxes[150100];

int dp[150100][11][2][2];

int solve(int id, int bought, int passed, int p) {
    if (dp[id][bought][passed][p] != -1000000000)
        return dp[id][bought][passed][p];

    if (id == n)
        return 0;

    int ret = 0;

    if (p == 0) {
        ret = solve(id+1, bought, passed, 0);

        if (bought < k+1)
            ret = max(ret, boxes[id].vs - boxes[id].cs + solve(id, bought+1, passed, 1));
    }
    else {
        if (!passed)
            ret = solve(id+1, bought, 1, 0);

        if (bought < k+1 || passed)
            ret = min(ret, - boxes[id].vs + solve(id+1, bought, passed, 0));
    }

    return dp[id][bought][passed][p] = ret;
}

bool cmp(box a, box b) {
    return a.cs < b.cs;
}

int main() {
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d", &n, &k);
        for (int i = 0; i < n; i++)
            scanf("%d %d", &boxes[i].vs, &boxes[i].cs);

        sort(boxes, boxes+n, cmp);

        for (int i = 0; i < 150100; i++)
            for (int j = 0; j < 11; j++)
                for (int l = 0; l < 2; l++)
                    for (int m = 0; m < 2; m++)
                        dp[i][j][l][m] = -1000000000;

        printf("%d\n", solve(0, 0, 0, 0));
    }
    return 0;
}

/*
18 5
368 27
69 79
423 31
132 10
75 61
478 69
266 59
144 16
102 23
455 23
52 41
19 62
96 95
4 67
370 40
319 64
495 38
21 40
*/

//267
