#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>

using namespace std;

#define EPS 1e-9

int t, h, s;
char spell[20];
double sum[22][22][440], aux[22][22][440];

int main() {
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j <= 20; j++) {
            sum[i][j][0] = 1;

            for (int k = 0; k < j; k++) {
                for (int l = 0; l < 440; l++) {
                    aux[i][j][l] = sum[i][j][l];
                    sum[i][j][l] = 0;
                }

                for (int l = 1; l <= i; l++)
                    for (int m = 0; m < 440; m++)
                        if (aux[i][j][m] > EPS)
                            sum[i][j][m+l] += aux[i][j][m];
            }

            for (int k = 438; k >= 0; k--)
                sum[i][j][k] += sum[i][j][k+1];
        }

    scanf("%d", &t);
    for (int tc = 0; tc < t; tc++) {
        scanf("%d %d", &h, &s);

        double maxi = 0.0;

        for (int i = 0; i < s; i++) {
            scanf("%s", spell);

            int times = 0, dice = 0, dif = 0, pos = 0;
            bool neg = false;

            while (spell[pos] != 'd') {
                times *= 10;
                times += spell[pos] - '0';
                pos++;
            }
            pos++;

            while (spell[pos] != '-' && spell[pos] != '+' && pos < strlen(spell)) {
                dice *= 10;
                dice += spell[pos] - '0';
                pos++;
            }

            if (pos < strlen(spell) && spell[pos] == '-') neg = true;

            pos++;
            while (pos < strlen(spell)) {
                dif *= 10;
                dif += spell[pos] - '0';
                pos++;
            }

            if (neg) dif *= -1;

            double div = 1;
            for (int j = 0; j < times; j++)
                div *= dice;

            if (maxi < sum[dice][times][min(401, max(0, h - dif))] / div)
                maxi = sum[dice][times][min(401, max(0, h - dif))] / div;
        }
        printf("Case #%d: %.6f\n", tc+1, maxi);
    }

    return 0;
}
