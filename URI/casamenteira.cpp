#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector < int > graph[110000];
map < string, int > ind;
bool visited[110000];
bool rec[110000];
int cycle = 0;

void dfs(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v]) {
            rec[u] = true;
            dfs(v);
            rec[u] = false;
        }
        else if (rec[v]) cycle++;
    }
}

int main() {
    string a, b;
    int c = 0;
    while(cin >> a >> b) {
        if (!ind.count(a)) ind[a] = c++;
        if (!ind.count(b)) ind[b] = c++;
        graph[ind[a]].push_back(ind[b]);
    }
    for (int i = 1; i <= c; i++) {
        if (!visited[i])
            dfs(i);
    }
    printf("%d\n", cycle);
    return 0;
}

