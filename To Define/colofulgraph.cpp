#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;

typedef pair < int, int > pii;

vector < int > comp, colors;
vector < pii > graph[110];
int visited[110], paths[110][110];

void dfs(int u, int color) {
    visited[u] = 1;
    comp.push_back(u);
    for (pii v : graph[u])
        if (!visited[v.first] && v.second == color)
            dfs(v.first, color);
}

int main() {
    int n, m, x, y, z;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        bool f = false;
        scanf("%d %d %d", &x, &y, &z);
        graph[x].push_back(make_pair(y,z));
        graph[y].push_back(make_pair(x,z));

        for (int j = 0; j < colors.size(); j++)
            if (colors[j] == z) f = true;

        if (!f) colors.push_back(z);
    }

    for (int i = 0; i < colors.size(); i++) {
        memset(visited, 0, sizeof visited);
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                dfs(j, colors[i]);

                if (comp.size() > 1) {
                    for (int k = 0; k < comp.size(); k++)
                        for (int l = k+1; l < comp.size(); l++) {
                            paths[comp[k]][comp[l]]++;
                            paths[comp[l]][comp[k]]++;
                        }
                }
                comp.clear();
            }
        }
    }

    int q;
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &x, &y);
        printf("%d\n", paths[x][y]);
    }

    return 0;
}
