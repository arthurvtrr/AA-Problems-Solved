#include <bits/stdc++.h>

using namespace std;

#define N 100100

int n, m, shots, details[N][5];
int RMQ[N][5][20], LOG[N];

void process() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < 5; j++)
            RMQ[i][j][0] = i;

    for (int k = 0; k < 5; k++)
        for (int j = 1; (1 << j) < N; j++)
            for (int i = 1; i + (1 << j) - 1 < N; i++) {
                if (details[RMQ[i][k][j-1]][k] > details[RMQ[i + (1 << (j - 1))][k][j - 1]][k])
                    RMQ[i][k][j] = RMQ[i][k][j-1];
                else
                    RMQ[i][k][j] = RMQ[i + (1 << (j - 1))][k][j - 1];
            }
}

void init() {
    for (int i = 0, ret = 0; i < N; i++)
        LOG[i] = ret += (i > 1 && !(i&(i - 1)));
}

int query(int i, int j, int a) {
    int k = LOG[j - i + 1];
    return max(details[RMQ[i][a][k]][a], details[RMQ[j - (1 << k) + 1][a][k]][a]);
}

int main() {
    scanf("%d %d %d", &n, &m, &shots);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &details[i][j]);

    init();
    process();

    int maxi = 0, best[5] = {0, 0, 0, 0, 0};

    for (int i = 1; i <= n; i++) {
        int ini = i, fim = n;

        while (ini <= fim) {
            int mid = (ini + fim) / 2;
            long long sum = 0;

            for (int j = 0; j < m; j++)
                sum += query(i, mid, j);

            if (sum <= shots) ini = mid+1;
            else fim = mid-1;
        }

        if (fim - i + 1 > maxi) {
            maxi = fim - i + 1;
            for (int j = 0; j < m; j++)
                best[j] = query(i, fim, j);
        }
    }

    for (int i = 0; i < m; i++) {
        if (i) printf(" ");
        printf("%d", best[i]);
    }
    printf("\n");

    return 0;
}
