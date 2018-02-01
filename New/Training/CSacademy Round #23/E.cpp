#include <bits/stdc++.h>

using namespace std;

int n, nums[2020], color[2020], matchs[2020];
vector < int > graph[2020], aux[2020];

bool prime[200200], visited[2020];

void sieve() {
    for (int i = 2; i < 200200; i++)
        prime[i] = true;

    for (int i = 2; i < 200200; i++)
        if (prime[i])
            for (int j = 2*i; j < 200200; j += i)
                prime[j] = false;
}

void set_colors(int u, int c) {
    visited[u] = true;
    color[u] = c;

    for (int v : graph[u])
        if (!visited[v])
            set_colors(v, 1 - c);
}

bool match_vertex(int u) {
    for (int v : aux[u])
        if (!visited[v]) {
            visited[v] = true;
            if (matchs[v] < 0 || match_vertex(matchs[v])) {
                matchs[v] = u;
                return true;
            }
        }
    return false;
}

int max_match() {
    memset(matchs, -1, sizeof(matchs));
    int result = 0;
    for (int u = 0; u <= n; u++) {
        memset(visited, 0, sizeof(visited));
        if (match_vertex(u)) result++;
    }
    return result;
}

void dfs(int u) {
    visited[u] = true;
    for (int v : graph[u])
        if (!visited[v]) {
            if (matchs[u] == v && color[u] < color[v]) dfs(v);
            else if (matchs[u] != v && color[u] > color[v]) dfs(v);
        }
}

int main() {
    sieve();

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    for (int i = 1; i <= n; i++)
        for (int j = i+1; j <= n; j++)
            if (prime[nums[i] + nums[j]]) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }

    for (int i = 1; i <= n; i++)
        if (!visited[i])
            set_colors(i, 1);

    for (int i = 1; i <= n; i++) {
        visited[i] = false;
        if (color[i] == 1)
            for (int v : graph[i])
                aux[i].push_back(v);
    }

    printf("%d\n", max_match());

    for (int i = 1; i <= n; i++) {
        visited[i] = false;
        if (matchs[i] != -1) matchs[matchs[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        bool valid = true;
        for (int v : graph[i])
            if (matchs[i] == v)
                valid = false;

        if (valid && color[i] == 1)
            dfs(i);
    }

    vector < int > ans;
    for (int i = 1; i <= n; i++)
        if ((color[i] == 1 && !visited[i]) || (color[i] == 0 && visited[i]))
            ans.push_back(i);

    for (int i = 0; i < ans.size(); i++) {
        if (i) printf(" ");
        printf("%d", nums[ans[i]]);
    }
    printf("\n");

    return 0;
}

