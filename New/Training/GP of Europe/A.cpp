#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, m;
char grid[120][120], mat[4][120][120];
bool used[120][120];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%s", grid[i]);

    int l = 0, c = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '#') {
                int aux = j;
                while (grid[i][aux] != '#') {
                    c++;
                    aux++;
                }
                aux = i;
                while (grid[aux][j] != '#') {
                    l++;
                    aux++;
                }
                found = true;
            }

            if (found) break;
        }
        if (found) break;
    }

    int cont = 0;

    for (int i = 1; i < n; i += l+1) {
        for (int j = 1; j < m; j += c+1) {
            if (used[i][j]) continue;
            cont++;

            for (int a = 0; a < l; a++)
                for (int b = 0; b < c; b++) {
                    used[a+i][b+j] = true;

                    mat[0][a][b] = grid[a+i][b+j];
                    mat[2][a][b] = grid[l-a-1+i][c-b-1+j];
                }

            for (int a = 0; a < c; a++)
                for (int b = 0; b < l; b++) {
                    mat[1][a][b] = grid[b+i][c-a-1+j];
                    mat[3][a][b] = grid[l-b-1+i][a+j];
                }

            for (int a = 1; a < n; a += l+1) {
                for (int b = 1; b < m; b += c+1) {
                    if (used[a][b]) continue;

                    for (int x = 0; x < 4; x++) {
                        bool valid = true;

                        for (int y = 0; y < l; y++)
                            for (int z = 0; z < c; z++)
                                if (grid[y+a][z+b] != mat[x][y][z])
                                    valid = false;

                        if (valid) {
                            for (int y = 0; y < l; y++)
                                for (int z = 0; z < c; z++)
                                    used[y+a][z+b] = true;
                        }
                    }
                }
            }

        }
    }

    printf("%d\n", cont);
    return 0;
}
