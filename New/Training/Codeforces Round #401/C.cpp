#include <bits/stdc++.h>

using namespace std;

#define N 100100
#define LOGN 30

int n, m, k, x, y;
vector < vector < int > > grid;
int upper[N];

int rmq[N][LOGN], LOG[N];

void processRMQ() {
    for (int i = 0, ret = 0; i < N; i++)
        LOG[i] = ret += (i > 1 && !(i&(i-1)));

    for (int i = 0; i < N; i++)
        rmq[i][0] = i;

    for (int j = 1; 1 << j < N; j++)
        for (int i = 0; i + (1 << j) - 1 < N; i++)
            if (upper[rmq[i][j - 1]] > upper[rmq[i + (1 << (j - 1))][j - 1]])
                rmq[i][j] = rmq[i][j - 1];
            else
                rmq[i][j] = rmq[i + (1 << (j - 1))][j - 1];
}

int RMQquery(int i, int j) {
    int k = LOG[j - i + 1];
    return max(upper[rmq[i][k]], upper[rmq[j - (1 << k) + 1][k]]);
}

int main() {
    scanf("%d %d", &n, &m);

    vector < int > row;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &x);
            row.push_back(x);
        }
        grid.push_back(row);
        row.clear();
    }
    for (int i = 0; i < m; i++)
        row.push_back(0);
    grid.push_back(row);

    for (int i = 1; i <= n; i++)
        upper[i] = i;

    for (int i = 0; i < m; i++) {
        int ini = 0;
        for (int j = 1; j <= n; j++)
            if (grid[j][i] < grid[j-1][i]) {
                upper[ini+1] = max(upper[ini+1], j);
                ini = j;
            }
    }

    processRMQ();
    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        scanf("%d %d", &x, &y);
        if (RMQquery(1, x) >= y) printf("Yes\n");
        else printf("No\n");
    }

    return 0;
}
