#include <bits/stdc++.h>
using namespace std;

struct point {
    int x, y;
};

vector<point> p;

point orig;
int n, dp[51][51];

bool ccw(point o, point i, point j) {
    int x1 = i.x - o.x, y1 = i.y - o.y;
    int x2 = j.x - o.x, y2 = j.y - o.y;
    return x1*y2 - x2*y1 >= 0;
}

bool cmp(const point &a, const point &b) {
    if (a.x == orig.x && a.y == orig.y) return false;
    if (b.x == orig.x && b.y == orig.y) return false;

    return ccw(orig, a, b);
}
/*
4
0 0
1 1
1 10
10 1
*/

int _try(int o, point origin) {
   // printf ("k = %d\n", o);
    //   for (int i = 0; i < n; i++)
     //   printf("%d %d\n", p[i].x, p[i].y);
    memset(dp, 0, sizeof dp);
    for (int i = 0; i < n; i++) dp[i][o] = 2;
    int ans = 0;
    for (int i = o; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            for (int k = j - 1; k >= 0; k--) {
                if (p[j].y < origin.y || p[k].y < origin.y || p[i].y < origin.y)
                    continue;
             //   printf ("%d %d %d\n", j, k, dp[j][k]);
                if (ccw(p[k], p[j], p[i])){
                    dp[i][j] = max(dp[i][j], dp[j][k] + 1);
             //   printf ("i(%d %d) j(%d %d) k(%d %d)    %d-%d\n", p[i].x, p[i].y, p[j].x, p[j].y, p[k].x, p[k].y, dp[i][j], dp[j][k]);
                }
                ans = max(ans, dp[i][j]);
            }
        }
    }

    return ans;
}

int main() {
    freopen ("convex.in", "r", stdin);
    freopen ("convex.out", "w", stdout);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p.push_back((point) {x, y});
    }

    vector < point > aux(p.begin(), p.end());

    int ans = 0;
    for (int i = 0; i < n; i++) {
        orig = (point) {aux[i].x, aux[i].y};
        sort(p.begin(), p.end(), cmp);
    //    for (int i = 0 ; i < n; i++){
    //        printf ("%d %d\n", p[i].x, p[i].y);
    //   }
        int k;
        for (int j = 0; j < n; j++)
            if (orig.x == p[j].x && orig.y == p[j].y )
                k = j;
        ans = max(ans, _try(k, orig));
    }

    printf("%d\n", ans);

    return 0;
}

