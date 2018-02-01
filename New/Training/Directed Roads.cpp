#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

#define MOD 1000000007

int n, x;
vector < int > graph[200100];
int times[200100], cont;
bool visited[200100], inStack[200100];
long long sol;

void dfs(int u, int t) {
    visited[u] = true;
    inStack[u] = true;
    times[u] = t;

    for (int v : graph[u]) {
        if (inStack[v]) {
            long long aux = 1;

            for (int i = 0; i < t - times[v] + 1; i++) {
                cont++;
                aux *= 2;
                aux %= MOD;
            }
            aux -= 2;
            sol *= aux;
            sol %= MOD;
        }
        else if (!visited[v]) dfs(v, t+1);
    }

    inStack[u] = false;
    times[u] = 0;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        graph[i].push_back(x);
    }

    sol = 1, cont = 0;

    for (int i = 1; i <= n; i++)
        if (!visited[i])
            dfs(i, 1);

    for (int i = 0; i < n - cont; i++) {
        sol *= 2;
        sol %= MOD;
    }

    printf("%lld\n", sol);

    return 0;
}

