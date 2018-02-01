#include <bits/stdc++.h>

using namespace std;

#define ll long long

int n, m;
ll a, b, nums[300300];
vector < int > graph[300300];

bool valid(int x, int y) {
    int ini = 0, fim = (int)graph[y].size()-1;

}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
        sort(graph[i].begin(), graph[i].end());

    int pos = 0;
    for (int i = 1; i <= n; i++) {
        pos = max(pos, i+1);
        while (pos <= n && valid(i, pos)) pos++;
        pos--;
        nums[i] = pos;
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", query(1, 1, n, a, b) - b*(b+1)/2 + a*(a-1)/2);
    }

    return 0;
}
