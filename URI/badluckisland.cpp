#include <stdio.h>

using namespace std;

double dp[110][110][110];

int main() {
    int r, s, p;
    scanf("%d %d %d", &r, &s, &p);
    for (int i = 0; i <= 100; i++) for (int j = 0; j <= 100; j++) for (int k = 0; k <= 100; k++) {
        double d = i*j + i*k + j*k;
        if (i == 0) dp[i][j][k] = 0.0;
        else if (k == 0) dp[i][j][k] = 1.0;
        else if (j == 0) dp[i][j][k] = 0.0;
        else dp[i][j][k] = (i * j / d * dp[i][j-1][k]) + (i * k / d * dp[i-1][j][k]) + (j * k / d * dp[i][j][k-1]);
    }

    printf("%.12lf %.12lf %.12lf\n", dp[r][s][p], dp[s][p][r], dp[p][r][s]);
    return 0;
}
