#include <stdio.h>
#include <math.h>

using namespace std;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    if (k > ceil(n*n / 2.0)) printf("NO\n");
    else {
        printf("YES\n");
        char matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) && k > 0) {
                    matrix[i][j] = 'L';
                    k--;
                }
                else matrix[i][j] = 'S';
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%c", matrix[i][j]);
            printf("\n");
        }
    }

    return 0;
}
