#include <bits/stdc++.h>

using namespace std;

int n;
string s;

int dp[100][100];

int solve(int ini, int fim, string left) {
    if (dp[ini][fim] != -1)
        return dp[ini][fim];

    if (ini >= fim) return 0;

    int ret = 10000000;

    if (left[ini] == 'V' && left[ini+1] == 'K') {
        string next = "";
        for (int i = 0; i < n; i++) next += left[i];
        swap(next[ini], next[ini+1]);

        ret = min(ret, 1 + solve(ini+1, fim, next));
    }
    else ret = min(ret, solve(ini+1, fim, left));

    if (left[fim-1] == 'V' && left[fim] == 'K') {
        string next = "";
        for (int i = 0; i < n; i++) next += left[i];
        swap(next[fim-1], next[fim]);

        ret = min(ret, 1 + solve(ini, fim-1, next));
    }
    else ret = min(ret, solve(ini, fim-1, left));

    return dp[ini][fim] = ret;
}

int main() {
    scanf("%d", &n);
    cin >> s;

    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            dp[i][j] = -1;

    printf("%d\n", solve(0, n-1, s));
    return 0;
}

