#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

#define INF 100000000

struct pos {
    int x;
    int y;
};

char mat[110][110];
bool visited[110][110];
int dist[110][110], sol;

bool to_use(char c, int m) {
    int pos = tolower(c) - 'a';
    bool x = (m >> pos) & 1;
    if (x && isupper(c)) return true;
    else if (!x && islower(c)) return true;
    return false;
}

void bfs(int n, int m) {
    queue < pos > fila;

    for (int i = 0; i < 110; i++)
        for (int j = 0; j < 110; j++) {
            visited[i][j] = false;
            dist[i][j] = INF;
        }

    if (!to_use(mat[0][0], m)) return;

    dist[0][0] = 1;
    fila.push((pos) {0,0});

    while (!fila.empty()) {
        pos u = fila.front();
        fila.pop();
        visited[u.x][u.y] = true;

        if (u.x - 1 >= 0 && !visited[u.x-1][u.y] && to_use(mat[u.x-1][u.y], m))
            if (dist[u.x-1][u.y] > dist[u.x][u.y] + 1) {
                dist[u.x-1][u.y] = dist[u.x][u.y] + 1;
                fila.push((pos) {u.x-1, u.y});
            }
        if (u.x + 1 < n && !visited[u.x+1][u.y] && to_use(mat[u.x+1][u.y], m))
            if (dist[u.x+1][u.y] > dist[u.x][u.y] + 1) {
                dist[u.x+1][u.y] = dist[u.x][u.y] + 1;
                fila.push((pos) {u.x+1, u.y});
            }
        if (u.y - 1 >= 0 && !visited[u.x][u.y-1] && to_use(mat[u.x][u.y-1], m))
            if (dist[u.x][u.y-1] > dist[u.x][u.y] + 1) {
                dist[u.x][u.y-1] = dist[u.x][u.y] + 1;
                fila.push((pos) {u.x, u.y-1});
            }
        if (u.y + 1 < n && !visited[u.x][u.y+1] && to_use(mat[u.x][u.y+1], m))
            if (dist[u.x][u.y+1] > dist[u.x][u.y] + 1) {
                dist[u.x][u.y+1] = dist[u.x][u.y] + 1;
                fila.push((pos) {u.x, u.y+1});
            }
    }
    if (dist[n-1][n-1] < sol) sol = dist[n-1][n-1];
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++)
            scanf("%s", mat[i]);

        sol = INF;
        for (int mask = 0; mask < (1 << 10); mask++)
            bfs(n, mask);

        if (sol == INF) printf("-1\n");
        else printf("%d\n", sol);
    }
    return 0;
}
