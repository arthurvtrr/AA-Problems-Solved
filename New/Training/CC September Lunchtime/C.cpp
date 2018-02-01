#include <bits/stdc++.h>

using namespace std;

int t, r, c, n, sx, sy;
int dx[10], dy[10];
int grid[1010][1010];

#define pii pair < int, int >
vector < pii > valids[1010][1010];

unordered_map < int, int > dp[1010][1010];

bool valid(int x, int y, int p, int cx,     int cy) {
    if (x + cx * dx[p] < 0) return false;
    if (x + cx * dx[p] >= r) return false;
    if (y + cy * dy[p] < 0) return false;
    if (y + cy * dy[p] >= c) return false;
    return true;
}

int solve(int x, int y, int p) {
    if (dp[x][y].count(p)) return dp[x][y][p];
    if (p == (1 << n) - 1) return 0;

    int ret = 0;

    for (pii v : valids[x][y])
        if (!(p & (1 << v.first))) {
            int a = (v.second & 1? -1 : 1) * dx[v.first];
            int b = (v.second < 3? -1 : 1) * dy[v.first];
            ret = max(ret, solve(x + a, y + b, p | (1 << v.first)) + grid[x + a][y + b]);
        }

    return dp[x][y][p] = ret;
}

inline bool ri(register int *n){
  register char ch;
  while ((ch = getchar_unlocked()) < '-');
  for (*n = ch - '0'; (ch = getchar_unlocked()) >= '0'; *n = ((*n * 5) << 1) + ch - '0');
  return true;
}

int main() {
    ri(&t);
    while (t--) {
        ri(&r); ri(&c); ri(&n);
        ri(&sx); ri(&sy);
        for (int i = 0; i < n; i++)
            ri(&dx[i]);
        for (int i = 0; i < n; i++)
            ri(&dy[i]);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                ri(&grid[i][j]);

        for (int i = 0; i <= r; i++)
            for (int j = 0; j <= c; j++) {
                dp[i][j].clear();
                valids[i][j].clear();
            }

        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                for (int k = 0; k < n; k++) {
                    if (valid(i, j, k, -1, -1)) valids[i][j].push_back(pii(k, 1));
                    if (valid(i, j, k, 1, -1)) valids[i][j].push_back(pii(k, 2));
                    if (valid(i, j, k, -1, 1)) valids[i][j].push_back(pii(k, 3));
                    if (valid(i, j, k, 1, 1)) valids[i][j].push_back(pii(k, 4));
                }

        int ans = solve(sx, sy, 0) + grid[sx][sy];
        printf("%d\n", ans);
    }
    return 0;
}
