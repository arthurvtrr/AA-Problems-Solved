#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

#define MOD 1000000007

int n, m, time = 0, lowlink[110000];
long long costs[110000];
vector < int > junctions[110000], test;
vector < vector < int > > components;
bool visited[110000];

void dfs(int u) {
    lowlink[u] = time++;
    visited[u] = true;
    test.push_back(u);
    bool isRoot = true;

    for (int v : junctions[u]) {
        if (!visited[v])
            dfs(v);
        if (lowlink[u] > lowlink[v]) {
            lowlink[u] = lowlink[v];
            isRoot = false;
        }
    }

    if (isRoot) {
        vector < int > component;
        while (true) {
            int x = test.back();
            test.pop_back();
            component.push_back(x);
            lowlink[x] = 2147483647;
            if (x == u)
                break;
        }
        components.push_back(component);
    }
}

int main()
{
    int a, b;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &costs[i]);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        junctions[a].push_back(b);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i])
            dfs(i);
    }

    long long possib, posb[110000];
    long long total = 0, menor;
    for (int i = 0; i < components.size(); i++) {
        menor = costs[components[i][0]];
        possib = 0;
        for (int u : components[i]) {
            if (costs[u] < menor) {
                menor = costs[u];
            }
        }
        for (int u : components[i]) {
            if (costs[u] == menor)
                possib++;
        }
        total += menor;
        posb[i] = possib;
    }

    possib = 1;
    for (int i = 0; i < components.size(); i++) {
        possib *= posb[i];
        possib %= MOD;
    }

    printf("%I64d %I64d", total, possib);
    printf("\n");

    return 0;
}