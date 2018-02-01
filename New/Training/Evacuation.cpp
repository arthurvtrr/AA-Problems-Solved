#include <bits/stdc++.h>

using namespace std;

#define N 1010
#define INF 1000000
#define pii pair <int, int>

int n, t;
char grid1[11][11], grid2[11][11];
int c_id[11][11], cap_id[11][11];
int dist[2][11][11];

bool valid(int a, int b, int x, int y, bool reactor) {
    bool ret = a + x >= 0 && a + x < n && b + y >= 0 && b + y < n
         && grid1[a+x][b+y] >= '0' && grid1[a+x][b+y] <= '9'
         && dist[reactor][a+x][b+y] > dist[reactor][a][b] + 1;

    if (!reactor) ret = ret && dist[1][a+x][b+y] > dist[0][a][b] + 1;
    return ret;
}

void bfs(int x, int y) {
    bool reactor = (grid1[x][y] == 'Z');

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            dist[reactor][i][j] = INF;

    queue < pii > fila;
    fila.push(make_pair(x, y));
    dist[reactor][x][y] = 0;

    while (!fila.empty()) {
        pii u = fila.front();
        fila.pop();

        if (valid(u.first, u.second, -1, 0, reactor)) {
            dist[reactor][u.first-1][u.second] = dist[reactor][u.first][u.second] + 1;
            fila.push(make_pair(u.first-1, u.second));
        }
        if (valid(u.first, u.second, 1, 0, reactor)) {
            dist[reactor][u.first+1][u.second] = dist[reactor][u.first][u.second] + 1;
            fila.push(make_pair(u.first+1, u.second));
        }
        if (valid(u.first, u.second, 0, -1, reactor)) {
            dist[reactor][u.first][u.second-1] = dist[reactor][u.first][u.second] + 1;
            fila.push(make_pair(u.first, u.second-1));
        }
        if (valid(u.first, u.second, 0, 1, reactor)) {
            dist[reactor][u.first][u.second+1] = dist[reactor][u.first][u.second] + 1;
            fila.push(make_pair(u.first, u.second+1));
        }
    }
}

vector < int > graph[N];
bool visited[N];
int matchs[N];

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
    for (int u = 0; u < N; u++) {
        memset(visited, 0, sizeof(visited));
        if (match_vertex(u)) result++;
    }
    return result;
}

bool reachable(int a, int b) {
    bool ret = dist[0][a][b] < dist[1][a][b] && dist[0][a][b] <= t;

    int mini = INF;
    if (a > 0) mini = min(mini, dist[0][a-1][b]);
    if (a < n-1) mini = min(mini, dist[0][a+1][b]);
    if (b > 0) mini = min(mini, dist[0][a][b-1]);
    if (b < n-1) mini = min(mini, dist[0][a][b+1]);

    return ret || (mini < dist[1][a][b] && mini + 1 <= t);
}

void gen_edges(int a, int b) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (grid2[i][j] >= '1' && grid2[i][j] <= '9' && reachable(i, j)) {
                for (int k = c_id[a][b]; k < c_id[a][b] + (grid1[a][b] - '0'); k++)
                    for (int l = cap_id[i][j]; l < cap_id[i][j] + (grid2[i][j] - '0'); l++)
                        graph[k].push_back(l);
            }
        }
}

int main() {
    scanf("%d %d", &n, &t);

    for (int i = 0; i < n; i++)
        scanf("%s", grid1[i]);
    for (int i = 0; i < n; i++)
        scanf("%s", grid2[i]);

    int cont = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid1[i][j] >= '1' && grid1[i][j] <= '9') {
                c_id[i][j] = cont;
                cont += grid1[i][j] - '0';
            }
    cont = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid2[i][j] >= '1' && grid2[i][j] <= '9') {
                cap_id[i][j] = cont;
                cont += grid2[i][j] - '0';
            }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid1[i][j] == 'Z')
                bfs(i, j);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (grid1[i][j] >= '1' && grid1[i][j] <= '9') {
                bfs(i, j);
                gen_edges(i, j);
            }

    printf("%d\n", max_match());

    return 0;
}
