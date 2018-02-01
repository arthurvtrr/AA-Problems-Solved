#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, m, nums[1010][1010], acuml[1010][1010], acumc[1010][1010];

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", &nums[i][j]);
            acuml[i][j] = acumc[i][j] = nums[i][j];
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            acuml[i][j] += acuml[i][j-1];

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            acumc[j][i] += acumc[j-1][i];

    int sol = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (nums[i][j] == 0) {
                if (acuml[i][m] - acuml[i][j] > 0) sol++;
                if (acuml[i][j] - acuml[i][0] > 0) sol++;
                if (acumc[n][j] - acumc[i][j] > 0) sol++;
                if (acumc[i][j] - acumc[0][j] > 0) sol++;
            }
        }
    }

    printf("%d\n", sol);

    return 0;
}
