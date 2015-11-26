#define N 40
#define M 35

vector < int > graph[M];
bool visited[N];
int matchs[N];
int n, m;

bool match_vertex(int u) {
    for (int v : graph[u])
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
    for (int u = 0; u < m; u++) {
        memset(visited, 0, sizeof(visited));
        if (match_vertex(u)) result++;
    }
    return result;
}
