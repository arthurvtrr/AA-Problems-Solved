#include <bits/stdc++.h>

using namespace std;

#define PI acos(-1)
#define EPS 1e-9

int n;
struct circle {
    long double x, y, r;
} circles[1100];

bool cmp(circle a, circle b) {
    return a.r < b.r;
}

bool inside(circle a, circle b) {
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)) < b.r;
}

vector < int > graph[1100];
int parent[1100];

long double dp[1100][3][3];

long double solve(int u, int la, int lb) {
    if (dp[u][la][lb] > -DBL_MAX + EPS) return dp[u][la][lb];

    long double ret = -DBL_MAX, a = 0.0, b = 0.0;
    for (int v : graph[u]) {
        a += solve(v, 1 - la, lb);
        b += solve(v, la, 1 - lb);
    }
    ret = max(ret, (la == 1? 1 : -1) * circles[u].r * circles[u].r * PI + a);
    ret = max(ret, (lb == 1? 1 : -1) * circles[u].r * circles[u].r * PI + b);

    return dp[u][la][lb] = ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%Lf %Lf %Lf", &circles[i].x, &circles[i].y, &circles[i].r);
    sort(circles, circles+n, cmp);

    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++)
            if (inside(circles[i], circles[j])) {
                parent[i] = j;
                graph[j].push_back(i);
                break;
            }

    for (int i = 0; i < 1100; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                dp[i][j][k] = -DBL_MAX;

    long double ans = 0.0;
    for (int i = 0; i < n; i++)
        if (!parent[i])
            ans += solve(i, 1, 1);
    printf("%.8Lf\n", ans);

    return 0;
}
