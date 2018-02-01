#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, nums[100100];
vector < int > graph[100100];

bool visited[100100];
vector < ll > siz;
ll s;

void dfs(int u) {
    visited[u] = true;
    s++;
    for (int v : graph[u])
        if (!visited[v])
            dfs(v);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &nums[i]);
        graph[i].push_back(nums[i]);
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        if (!visited[i]) {
            s = 0;
            dfs(i);
            siz.push_back(s);
        }

    if (siz.size() == 1) printf("%lld\n", siz[0]*siz[0]);
    else {
        sort(siz.begin(), siz.end());
        for (int i = 0; i < (int)siz.size()-2; i++)
            ans += siz[i]*siz[i];
        ll aux = siz[(int)siz.size()-2] + siz.back();
        ans += aux*aux;

        printf("%lld\n", ans);
    }

    return 0;
}

