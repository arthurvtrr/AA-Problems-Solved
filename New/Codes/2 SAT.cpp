#include <stdio.h>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

#define JUMP 100050

int n, a, b, counter = 1, scc = 1, nums[100100], value[100100];
map < int, int > found;

bool visited[200100], new_edges[200100];
int dfs_num[200100], dfs_low[200100], cp[200100];

vector < int > graph[200100], new_graph[200100], comp[200100], aux, used, toposort;

void dfs(int u) {
    dfs_low[u] = dfs_num[u] = counter++;
    aux.push_back(u);
    visited[u] = true;

    for (int v : graph[u]) {
        if (!dfs_num[v])
            dfs(v);
        if (visited[v])
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {
        while (1) {
            int v = aux.back();
            aux.pop_back();
            visited[v] = false;

            comp[scc].push_back(v);
            cp[v] = scc;

            if (u == v) break;
        }
        scc++;
    }
}

void create_new_graph() {
    for (int i = 1; i < scc; i++) {
        for (int j = 0; j < used.size(); j++)
            new_edges[used[j]] = false;

        used.clear();

        for (int j = 0; j < comp[i].size(); j++)
            for (int v : graph[comp[i][j]])
                if (cp[v] != i && !new_edges[cp[v]]) {
                    new_graph[i].push_back(cp[v]);
                    used.push_back(cp[v]);
                    new_edges[cp[v]] = true;
                }
    }
}

void Tsort(int u) {
    dfs_num[u] = 1;
    for (int v : new_graph[u])
        if (!dfs_num[v])
            Tsort(v);
    toposort.push_back(u);
}

void set_values() {
    for (int i = 0; i < 100100; i++)
        value[i] = -1;

    for (int i = toposort.size()-1; i >= 0; i--)
        for (int v : comp[toposort[i]])
            if (v < JUMP && value[v] == -1)
                value[v] = 1;
            else if (v > JUMP && value[v-JUMP] == -1)
                value[v-JUMP] = 0;
}

int main() {
    scanf("%d %d %d", &n, &a, &b);

    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        found[nums[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        int cont = 0;

        if (found.count(a - nums[i-1])) {
            cont++;
            graph[i].push_back(found[a - nums[i-1]]+1);
            graph[found[a - nums[i-1]]+1+JUMP].push_back(i+JUMP);
        }
        else graph[i].push_back(i+JUMP);

        if (found.count(b - nums[i-1])) {
            cont++;
            graph[i+JUMP].push_back(found[b - nums[i-1]]+1+JUMP);
            graph[found[b - nums[i-1]]+1].push_back(i);
        }
        else graph[i+JUMP].push_back(i);

        if (cont == 0) {
            printf("NO\n");
            exit(0);
        }
    }

    for (int i = 1; i <= n; i++)
        if (!dfs_num[i])
            dfs(i);
    for (int i = JUMP+1; i <= JUMP+n; i++)
        if (!dfs_num[i])
            dfs(i);

    for (int i = 1; i <= n; i++)
        if (cp[i] == cp[i+JUMP]) {
            printf("NO\n");
            exit(0);
        }

    create_new_graph();

    for (int i = 0; i < 200100; i++)
        dfs_num[i] = 0;

    for (int i = 1; i < scc; i++)
        if (!dfs_num[i])
            Tsort(i);

    set_values();

    printf("YES\n");
    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        printf("%d", value[i]);
    }
    printf("\n");

    return 0;
}

