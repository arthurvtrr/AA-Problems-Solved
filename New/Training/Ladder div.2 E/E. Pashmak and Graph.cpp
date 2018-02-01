#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

#define pii pair < int, int >

int n, m, x, y, z;
pii edges[300300];
vector < pii > graph[300300];
map < pii, int > dp;

int solve(int id, int last) {
    if (dp.count(make_pair(id, last)))
        return dp[make_pair(id, last)];

    int ret = 0;
    for (pii v : graph[id])
        if (v.second > last)
            ret = max(ret, 1 + solve(v.first, v.second));

    return dp[make_pair(id, last)] = ret;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &z);
        graph[x].push_back(make_pair(y,z));
        graph[y].push_back(make_pair(x,z));
    }

    int sol = 0;
    for (int i = 1; i <= n; i++)
        sol = max(sol, solve(i, 0));

    printf("%d\n", sol);
    return 0;
}
