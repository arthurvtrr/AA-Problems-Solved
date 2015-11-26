#include <stdio.h>
#include <algorithm>

using namespace std;

int nums[2200], accsum[2200], dp1[2200][22], dp2[2200][22];

struct aux {
    int v;
    int l;
};

bool comp(aux x, aux y) {
    if (x.v < y.v) return true;
    if (y.v < x.v) return false;
    return x.l > y.l;
};

int val(int x) {
    if (x % 10 < 5) return x - (x % 10);
    return x - (x % 10) + 10;
}

void calc(int i, int j) {
    aux auxs[3];
    auxs[0].v = dp1[i][j-1], auxs[0].l = dp2[i][j-1];
    auxs[1].v = dp1[i-1][j-1] + val(nums[i]), auxs[1].l = i;
    auxs[2].v = dp2[i-1][j] == 0? val(accsum[i]) : dp1[dp2[i-1][j]-1][j] + val(accsum[i] - accsum[dp2[i-1][j]-1]), auxs[2].l = dp2[i-1][j];
    sort(auxs, auxs+3, comp);
    dp1[i][j] = auxs[0].v;
    dp2[i][j] = auxs[0].l;
}

int main() {
    int n, d;
    while(scanf("%d %d", &n, &d) != EOF) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &nums[i]);
            sum += nums[i];
            accsum[i] = sum;
        }

        for (int i = 0; i < n; i++) {
            dp1[i][0] = val(accsum[i]);
            dp2[i][0] = 0;
        }
        for (int i = 0; i < 22; i++) {
            dp1[0][i] = dp1[0][0];
            dp2[0][i] = 0;
        }

        for (int i = 1; i < n; i++)
            for (int j = 1; j <= d; j++)
                calc(i,j);

        printf("%d\n", dp1[n-1][d]);
    }
    return 0;
}
