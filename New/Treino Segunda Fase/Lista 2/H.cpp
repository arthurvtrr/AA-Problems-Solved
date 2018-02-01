#include <bits/stdc++.h>

using namespace std;

#define INF 100000000

int n, h, dists[1010], pos[1010];
int dp[2][50050];

int main() {
    while (1) {
        scanf("%d %d", &n, &h);
        if (n == -1 && h == -1) break;
        for (int i = 0; i < n-1; i++) {
            scanf("%d", &dists[i]);
            pos[i+1] = pos[i] + dists[i];
        }

        if (pos[n-1] > h*(n-1)) {
            printf("-1\n");
            continue;
        }

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < h*(n-1) + 10; j++)
                dp[i][j] = INF;

        dp[0][0] = 0;

        deque < int > aux;
        for (int i = 1; i < n-1; i++) {
            aux.clear();
            int p = i-1;
            for (int j = i; j <= i*h; j++) {
                while (p < j) {
                    while (!aux.empty() && dp[(i-1)&1][aux.back()] >= dp[(i-1)&1][p]) aux.pop_back();
                    aux.push_back(p);
                    p++;
                }
                while (!aux.empty() && j - aux.front() > h) aux.pop_front();

                if (aux.empty()) dp[i&1][j] = INF;
                else dp[i&1][j] = dp[(i-1)&1][aux.front()] + 1;
            }

            if (dp[i&1][pos[i]] < INF) dp[i&1][pos[i]]--;
        }

        int ans = INF;
        for (int i = 1; i <= h; i++)
            ans = min(ans, dp[(n-2) & 1][pos[n-1] - i]);

        printf("%d\n", ans);
    }
    return 0;
}
