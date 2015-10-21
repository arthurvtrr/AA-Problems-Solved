#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

typedef vector < int > vi;
typedef vector < vi > vvi;
vvi reactors(55);
int n, m;
long long danger = 1;
bool visited[55];

void dfs(int u) {
    visited[u] = true;
    for (int i = 0; i < reactors[u].size(); i++) {
        if (visited[reactors[u][i]] == false) {
            dfs(reactors[u][i]);
            danger *= 2;
        }
    }
}

int main()
{
    for(int j = 1; j <= n; j++) { visited[j] = false; }

    int a, b;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        reactors[a].push_back(b);
        reactors[b].push_back(a);
    }

    for (int i = 1; i <= n; i++){
        if (!visited[i])
            dfs(i);
    }

    printf("%I64d", danger);
    return 0;
}