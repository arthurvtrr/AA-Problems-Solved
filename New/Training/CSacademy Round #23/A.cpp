#include <bits/stdc++.h>

using namespace std;

int n, games[110][110];
int vict[110];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &games[i][j]);
            if (i != j) {
                if (games[i][j] == 1) vict[i]++;
                else vict[j]++;
            }
        }

    int winner = 0, maxi = 0;
    for (int i = 0; i < n; i++)
        if (vict[i] > maxi) {
            maxi = vict[i];
            winner = i;
        }

    printf("%d\n", winner+1);

    return 0;
}
