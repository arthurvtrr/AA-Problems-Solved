#include <stdio.h>
#include <algorithm>

using namespace std;

int t, a, b, c;
long long heap[25][25][25], col_s[25][25];
long long pieces[170000][25];
long long sol;

void solve(int &cont, int p, int x, int y) {
    for (int j = 1; j <= c; j++)
        for (int i = 1; i <= b; i++) {
            col_s[i][j] = heap[p][i][j];
            col_s[i][j] += col_s[i-1][j];
        }

    for (int i = x; i <= b; i++) {
        long long aux = 0;
        for (int j = y; j <= c; j++) {
            aux += col_s[i][j] - col_s[x-1][j];
            pieces[cont++][p] = aux;
        }
    }
}

int main() {
    scanf("%d", &t);

    for (int tc = 0; tc < t; tc++) {

        scanf("%d %d %d", &a, &b, &c);

        for (int i = 1; i <= a; i++)
            for (int j = 1; j <= b; j++)
                for (int k = 1; k <= c; k++)
                    scanf("%lld", &heap[i][j][k]);

        sol = -99999999999999999;

        int cont;
        for (int p = 1; p <= a; p++) {
            cont = 0;
            for (int i = 1; i <= b; i++)
                for (int j = 1; j <= c; j++)
                    solve(cont, p, i, j);
        }

        for (int i = 0; i < cont; i++) {
            long long maxi = -99999999999999999, sum = 0;
            for (int j = 1; j <= a; j++) {
                sum += pieces[i][j];
                maxi = max(maxi, sum);
                if (sum < 0)
                    sum = 0;
            }
            sol = max(maxi, sol);
        }

        if (tc != 0) printf("\n");
        printf("%lld\n", sol);
    }
    return 0;
}
