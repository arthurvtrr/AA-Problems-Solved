#include <stdio.h>

using namespace std;

int mat[10][10];
bool visited[10][10];

void dfs(int i, int j) {
    visited[i][j] = true;
    if (i-1 >= 0 && !visited[i-1][j] && mat[i-1][j] == 0) dfs(i-1, j);
    if (i+1 < 5 && !visited[i+1][j] && mat[i+1][j] == 0) dfs(i+1, j);
    if (j-1 >= 0 && !visited[i][j-1] && mat[i][j-1] == 0) dfs(i, j-1);
    if (j+1 < 5 && !visited[i][j+1] && mat[i][j+1] == 0) dfs(i, j+1);

}

int main() {
    int t;
    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                scanf("%d", &mat[i][j]);

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                visited[i][j] = false;

        dfs(0,0);

        if (visited[4][4]) printf("COPS\n");
        else printf("ROBBERS\n");
    }
    return 0;
}
