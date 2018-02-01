#include <bits/stdc++.h>

using namespace std;

int n, m, nums[100100];
vector < int > adj[100100];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < m; i++) {
        if (i > 0 && nums[i-1] != nums[i]) adj[nums[i]].push_back(nums[i-1]);
        if (i < m-1 && nums[i+1] != nums[i]) adj[nums[i]].push_back(nums[i+1]);
    }

    for (int i = 1; i <= n; i++)
        sort(adj[i].begin(), adj[i].end());

    long long ans = 0, initial = 0;
    for (int i = 1; i < m; i++)
        ans += abs(nums[i] - nums[i-1]);
    initial = ans;

    for (int i = 1; i <= n; i++)
        if (adj[i].size() > 0) {
            long long x = 0;
            for (int j = 0; j < adj[i].size(); j++)
                x += abs(i - adj[i][j]);

            long long y = 0;
            int siz = adj[i].size(), med = 0;
            if (siz % 2) med = adj[i][siz/2];
            else med = (adj[i][siz/2-1] + adj[i][siz/2]) / 2;
            for (int j = 0; j < adj[i].size(); j++)
                y += abs(med - adj[i][j]);

            ans = min(ans, initial - x + y);
        }

    printf("%lld\n", ans);

    return 0;
}
