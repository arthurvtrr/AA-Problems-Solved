#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

int n, k, x, y, subs[200200];
bool chosen[200200];
vector < int > graph[200200];

void calc(int u, int p) {
    subs[u] = chosen[u];

    if (graph[u].size() == 1 && p != 0) return;

    for (int v : graph[u])
        if (v != p) {
            calc(v, u);
            subs[u] += subs[v];
        }
}

int city;

void dfs(int u, int p) {
    bool valid = false;
    for (int v : graph[u])
        if (v != p && subs[v] > k) {
            dfs(v, u);
            valid = true;
        }

    if (!valid) city = u;
}

vector < int > aux;

void solve(int u, int p) {
    if (chosen[u]) aux.push_back(u);

    for (int v : graph[u])
        if (v != p)
            solve(v, u);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n-1; i++) {
        scanf("%d %d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    for (int i = 0; i < 2*k; i++) {
        scanf("%d", &x);
        chosen[x] = true;
    }

    calc(1, 0);
    dfs(1, 0);
    solve(city, 0);

    printf("1\n");
    printf("%d\n", city);
    for (int i = 0; i < k; i++)
        printf("%d %d %d\n", aux[i], aux[i+k], city);

    return 0;
}
