#include <bits/stdc++.h>

using namespace std;

#define state vector < int >

int n, nums[1010];
state dp[1010][1010];

state solve(int last, int ind) {
    if (dp[last][ind] != state({-1, -1, -1}))
        return dp[last][ind];

    if (ind >= n) return dp[last][ind] = state({nums[last], last, -1});
    else if (ind == n-1) return dp[last][ind] = state({max(nums[last], nums[ind]), last, ind});
    else {
        vector < int > choices = {last, ind, ind+1};

        state ret = {1000000000, 0, 0};
        for (int i = 0; i < 3; i++)
            for (int j = i+1; j < 3; j++)
                for (int k = 0; k < 3; k++)
                    if (k != i && k != j) {
                        state aux = solve(choices[k], ind+2);
                        if (max(nums[choices[i]], nums[choices[j]]) + aux[0] < ret[0])
                            ret = {max(nums[choices[i]], nums[choices[j]]) + aux[0], choices[i], choices[j]};
                    }
        return dp[last][ind] = ret;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &nums[i]);

    for (int i = 0; i < 1010; i++)
        for (int j = 0; j < 1010; j++)
            dp[i][j] = state({-1, -1, -1});

    solve(0, 1);
    printf("%d\n", dp[0][1][0]);

    int a = 0, b = 1;
    while (a < n) {
        int x = dp[a][b][1], y = dp[a][b][2];

        if (y == -1) {
            printf("%d\n", x+1);
            break;
        }

        printf("%d %d\n", x+1, y+1);
        vector < int > aux = {a, b, b+1};
        for (int i = 0; i < 3; i++)
            if (aux[i] != x && aux[i] != y)
                a = aux[i];
        b += 2;
    }

    return 0;
}
