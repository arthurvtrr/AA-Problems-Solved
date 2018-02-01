#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n, m, _y0, _y1, rats[110000], cheese[110000];
int choices[110000][5], dp[110000][5];

int solve(int ind, int last) {
    if (dp[ind][last] != -1)
        return dp[ind][last];

    if (ind == n) return 0;

    int ret = -100000;

    if (last == 2 || choices[ind-1][last] != choices[ind][0])
        ret = max(ret, 1 + solve(ind+1, 0));
    else if (abs(choices[ind-1][last] - rats[ind-1]) == abs(choices[ind][0] - rats[ind]))
        ret = max(ret, 1 + solve(ind+1, 0));

    if (last == 2 || choices[ind-1][last] != choices[ind][1])
        ret = max(ret, 1 + solve(ind+1, 1));
    else if (abs(choices[ind-1][last] - rats[ind-1]) == abs(choices[ind][1] - rats[ind]))
        ret = max(ret, 1 + solve(ind+1, 1));

    ret = max(ret, solve(ind+1, last));

    return dp[ind][last] = ret;
}

int binarySearch(int x) {
    int l = 0, r = m-1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (cheese[mid] == x) return mid;
        if (cheese[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

int main() {
    scanf("%d %d %d %d", &n, &m, &_y0, &_y1);

    for (int i = 0; i < n; i++)
        scanf("%d", &rats[i]);
    for (int i = 0; i < m; i++)
        scanf("%d", &cheese[i]);

    for (int i = 0; i < n; i++) {
        int pos = binarySearch(rats[i]);
        int a = abs(cheese[pos-1] - rats[i]), b = abs(cheese[pos] - rats[i]);

        choices[i][0] = a <= b? cheese[pos-1] : cheese[pos];
        choices[i][1] = b <= a? cheese[pos] : cheese[pos-1];

        if (pos == 0) choices[i][0] = choices[i][1] = cheese[pos];
    }

    for (int i = 0; i < 110000; i++)
        for (int j = 0; j < 5; j++)
            dp[i][j] = -1;

    printf("%d\n", n - solve(0, 2));
    return 0;
}
