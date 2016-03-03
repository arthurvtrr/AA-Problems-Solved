#include <stdio.h>

using namespace std;

bool visited[550][550];
char mat[550][550];

void dfs(int i, int j, int n, int m) {
    visited[i][j] = true;
    if (i-1 >= 0 && mat[i-1][j] == '.' && !visited[i-1][j]) dfs(i-1, j, n, m);
    if (i+1 < n && mat[i+1][j] == '.' && !visited[i+1][j]) dfs(i+1, j, n, m);
    if (j-1 >= 0 && mat[i][j-1] == '.' && !visited[i][j-1]) dfs(i, j-1, n, m);
    if (j+1 < m && mat[i][j+1] == '.' && !visited[i][j+1]) dfs(i, j+1, n, m);
}

int main() {
    int n, m, r1, c1, r2, c2;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", mat[i]);
    scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

    visited[r1-1][c1-1] = true;

    int viz = 0;
    if (r2-2 >= 0 && (mat[r2-2][c2-1] == '.' || visited[r2-2][c2-1])) viz++;
    if (r2 < n && (mat[r2][c2-1] == '.' || visited[r2][c2-1])) viz++;
    if (c2-2 >= 0 && (mat[r2-1][c2-2] == '.' || visited[r2-1][c2-2])) viz++;
    if (c2 < m && (mat[r2-1][c2] == '.' || visited[r2-1][c2])) viz++;

    if (mat[r2-1][c2-1] == '.' && viz < 2) printf("NO\n");
    else if (mat[r2-1][c2-1] == 'X' && viz < 1) printf("NO\n");
    else {
        mat[r2-1][c2-1] = '.';
        dfs(r1-1, c1-1, n, m);
        if (visited[r2-1][c2-1]) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
