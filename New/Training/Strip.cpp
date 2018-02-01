#include <bits/stdc++.h>

using namespace std;

#define N 100100
#define pii pair < int, int >

int n, s, l, nums[N];

int RMQ[N][20][2], LOG[N];

void process() {
    for (int i = 0; i < N; i++)
        RMQ[i][0][0] = RMQ[i][0][1] = i;

    for (int j = 1; (1 << j) < N; j++)
        for (int i = 1; i + (1 << j) - 1 < N; i++) {
            if (nums[RMQ[i][j-1][0]] > nums[RMQ[i + (1 << (j - 1))][j - 1][0]])
                RMQ[i][j][0] = RMQ[i][j-1][0];
            else
                RMQ[i][j][0] = RMQ[i + (1 << (j - 1))][j - 1][0];
        }

    for (int j = 1; (1 << j) < N; j++)
        for (int i = 1; i + (1 << j) - 1 < N; i++) {
            if (nums[RMQ[i][j-1][1]] < nums[RMQ[i + (1 << (j - 1))][j - 1][1]])
                RMQ[i][j][1] = RMQ[i][j-1][1];
            else
                RMQ[i][j][1] = RMQ[i + (1 << (j - 1))][j - 1][1];
        }
}

void init() {
    for (int i = 0, ret = 0; i < N; i++)
        LOG[i] = ret += (i > 1 && !(i&(i - 1)));
}

int query(int i, int j, int t) {
    int k = LOG[j - i + 1];
    if (t == 0) return max(nums[RMQ[i][k][t]], nums[RMQ[j - (1 << k) + 1][k][t]]);
    return min(nums[RMQ[i][k][t]], nums[RMQ[j - (1 << k) + 1][k][t]]);
}

int first[N], dp[N];

int main() {
    scanf("%d %d %d", &n, &s, &l);
    for (int i = 1; i <= n; i++)
        scanf("%d", &nums[i]);

    init();
    process();

    int ini = 1;
    for (int i = 1; i <= n; i++) {
        while (query(ini, i, 0) - query(ini, i, 1) > s) ini++;
        first[i] = ini;
    }

    deque < int > aux;
    aux.push_back(0);

    for (int i = 1; i <= n; i++) {
        if (i - first[i] + 1 < l) continue;

        while (!aux.empty() && aux.front()+1 < first[i]) aux.pop_front();
        if (dp[i-l]) {
            while (!aux.empty() && dp[aux.back()] > dp[i-l]) aux.pop_back();
            aux.push_back(i-l);
        }

        if (aux.empty()) dp[i] = 0;
        else dp[i] = dp[aux.front()] + 1;
    }

    printf("%d\n", dp[n] != 0? dp[n] : -1);

    return 0;
}
