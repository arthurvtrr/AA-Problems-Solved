#include <bits/stdc++.h>

using namespace std;

#define pll pair <long long, long long>

int n, quant[100100], x, y, root;
vector < int > graph[100100];

bool cmp(long long a, long long b) {
    return a > b;
}

pll dp[100100];

pll solve(int id, int p) {
    if (dp[id] != pll(0, 0))
        return dp[id];

    if (graph[id].size() == 1 && graph[id][0] == p)
        return pll(1, quant[id] - 1);

    long long left = quant[id] - (id != root? 1 : 0), gain = (id != root? 1 : 0), sum = 0;
    vector < long long > aux;
    for (int v : graph[id])
        if (v != p) {
            pll vs = solve(v, id);
            aux.push_back(vs.first);
            sum += vs.second;
        }

    sort(aux.begin(), aux.end(), cmp);

    int pos = 0;
    while (left && pos < aux.size()) {
        left--;
        gain += 1 + aux[pos++];
    }

    long long mini = min(left, sum);
    gain += 2 * mini;
    left -= mini;

    return dp[id] = pll(gain, left);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &quant[i]);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    scanf("%d", &root);
    printf("%lld\n", solve(root, 0).first);

    return 0;
}
